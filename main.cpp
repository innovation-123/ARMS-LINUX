#include <iostream>
#include <filesystem>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>
#include <map>
#include <sstream>
#include <opencv2/opencv.hpp>
#include <mutex>

#include "general_utils.h"
#include "PickleWriter.h"
#include "SerialPort.h"

std::atomic_bool stop_flag = false;
std::atomic_int file_counter = 0;
std::vector<std::map<std::string, std::vector<float>>> mapWritten;
cv::VideoCapture cap(0);
std::mutex mapWrittenMutex;  // Mutex to synchronize access to mapWritten

void serialThread(SerialPort& serial, SerialPort& serialSlave) {
    while (!stop_flag) {
        std::string command = "{\"T\":105}\n";
        if (!serial.send(command) || !serialSlave.send(command)) {
            std::cerr << "Failed to send command to master or slave.\n";
            continue;
        }

        std::string response, slaveResponse;
        for (int retries = 0; retries < 5; ++retries) {
            response = serial.receive();
            slaveResponse = serialSlave.receive();
            if (!response.empty() && !slaveResponse.empty()) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        if (response.empty() || slaveResponse.empty()) {
            std::cerr << "Error: No data received. Skipping iteration.\n";
            continue;
        }

        try {
            float shoulder = extractValue(slaveResponse, "s");
            float base = extractValue(slaveResponse, "b");
            float elbow = extractValue(slaveResponse, "e");
            float extension = extractValue(slaveResponse, "t");
            std::map<std::string, std::vector<float>> currentData = {
                {"joint_positions", {shoulder, base, elbow, extension}}
            };

            if (!mapWritten.empty()) {
                mapWritten.back()["control"] = {shoulder, base, elbow, extension};
            }

            {
                std::lock_guard<std::mutex> lock(mapWrittenMutex);  // Locking access to mapWritten
                mapWritten.push_back(currentData);
            }

            int count = file_counter.fetch_add(1);
            std::cout << "Processed iteration " << count << "\n";
            std::cout << response << "\n";

            float x = extractValue(slaveResponse, "x");
            float y = extractValue(slaveResponse, "y");
            float z = extractValue(slaveResponse, "z");
         /*   if (!isWithinSafeZone(x, y, z)) {
                std::cerr << "Arm is out of the safe zone! Stopping...\n";
                std::string stopCommand = "{\"T\":102,\"spd\":0,\"acc\":0,\"base\":0,\"shoulder\":0,\"elbow\":0,\"hand\":0}\n";
                serialSlave.send(stopCommand);
                stop_flag = true;
                break;
            }*/

            float s = extractValue(response, "s");
            float b = extractValue(response, "b");
            float e = extractValue(response, "e");
            float t = extractValue(response, "t");
            std::ostringstream commandStream;
            commandStream << "{\"T\":102,\"base\":" << b
                          << ",\"shoulder\":" << s
                          << ",\"elbow\":" << e
                          << ",\"hand\":" << t
                          << ",\"spd\":0,\"acc\":0}\n";
            serialSlave.send(commandStream.str());
        } catch (const std::exception& ex) {
            std::cerr << "Error: " << ex.what() << "\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
}

void cameraThread(const std::string& imageDir) {
    int prevCount = -1;
    while (!stop_flag) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Failed to capture frame from camera.\n";
            continue;
        }
        bool flagChanged=false;
        int count = file_counter.load();
        if (count != prevCount) {
            flagChanged=true;
            prevCount = count;
        }
      //  if(flagChanged){
        std::string filename = imageDir + "/frame_" + std::to_string(count) + ".jpg";
        cv::imwrite(filename, frame);
        std::cout << "Saved image: " << filename << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    //}
    cap.release();
    }
}

int main() {
    SerialPort serial, serialSlave;
    std::string desired_port, slave_port;

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera.\n";
        return -1;
    }
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    auto ports = list_ports();
    if (ports.empty()) {
        std::cerr << "No serial ports detected.\n";
        return -1;
    }
    std::cout << "Available Ports:\n";
    for (const auto& port : ports) {
        std::cout << "  " << port << "\n";
    }

    std::cout << "Enter the master port to connect (default /dev/ttyUSB0): ";
    std::getline(std::cin, desired_port);
    if (desired_port.empty()) {
        desired_port = "/dev/ttyUSB0";
    }

    if (!serial.connect(desired_port, 115200)) {
        std::cerr << "Failed to connect to " << desired_port << "\n";
        return 1;
    }
    std::cout << "Master Connected to " << desired_port << "\n";
    std::cout << "Enter the slave port to connect (default /dev/ttyUSB1): ";
    std::getline(std::cin, slave_port);
    if (slave_port.empty()) {
        slave_port = "/dev/ttyUSB1";
    }

    if (!serialSlave.connect(slave_port, 115200)) {
        std::cerr << "Failed to connect to " << slave_port << "\n";
        return 1;
    }
    std::cout << "Slave Connected to " << slave_port << "\n";

    std::string initialCommand = "{\"T\":210,\"cmd\":0}\n";
    if (serial.send(initialCommand)) {
        std::cout << "Sent initial command to master...\n";
        std::string response = serial.receive();
        std::cout << "Received response from master: " << response << "\n";
    }

    std::string timestamp = getTimestamp();
    std::string pickleDir = "pickles/" + timestamp;
    std::string imageDir = "camera_images/" + timestamp;
    std::filesystem::create_directories(pickleDir);
    std::filesystem::create_directories(imageDir);

    std::thread serialWorker(serialThread, std::ref(serial), std::ref(serialSlave));
    std::thread cameraWorker(cameraThread, imageDir);

    std::cout << "Press Enter to stop...\n";
    std::cin.get();

    stop_flag = true;
    serialWorker.join();
    cameraWorker.join();
    serial.disconnect();
    serialSlave.disconnect();

    for (int j = 0; j < mapWritten.size(); j++) {
        std::string filename = pickleDir + "/data_" + std::to_string(j) + ".pkl";
        try {
            PickleWriter pickle(filename);
            pickle.writeHeader();
            pickle.writeFloatArrayDict(mapWritten[j]);
            pickle.writeStop();
            std::cout << "Successfully wrote file: " << filename << "\n";
        } catch (const std::exception& ex) {
            std::cerr << "Error writing file " << filename << ": " << ex.what() << "\n";
        }
    }

    return 0;
}
