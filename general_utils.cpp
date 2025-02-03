#include "general_utils.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

std::vector<std::string> list_ports() {
    std::vector<std::string> ports;
    const std::string basePath = "/dev/";
    DIR* dir = opendir(basePath.c_str());
    if (dir == nullptr) {
        throw std::runtime_error("Error: Unable to open /dev directory");
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (std::string(entry->d_name).find("tty") == 0) {
            ports.push_back(basePath + entry->d_name);
        }
    }

    closedir(dir);
    return ports;
}

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

const float minX = -50.0, maxX = 381.7;
const float minY = -50.0, maxY = 8.245916;
const float minZ = 0.0, maxZ = 330.0;

bool isWithinSafeZone(float x, float y, float z) {
    return (x >= minX && x <= maxX && 
            y >= minY && y <= maxY && 
            z >= minZ && z <= maxZ);
}

float extractValue(const std::string& response, const std::string& key) {
    size_t keyPos = response.find("\"" + key + "\":");
    if (keyPos == std::string::npos) {
        throw std::runtime_error("Key '" + key + "' not found in response");
    }

    size_t valueStart = response.find(":", keyPos) + 1;
    size_t valueEnd = response.find(",", valueStart);
    if (valueEnd == std::string::npos) {
        valueEnd = response.find("}", valueStart);
    }

    std::string valueStr = response.substr(valueStart, valueEnd - valueStart);
    return std::stof(valueStr);
}
