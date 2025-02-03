#include "SerialPort.h"
#include <iostream>
#include <unistd.h>  // close()
#include <fcntl.h>   // open(), O_RDWR, O_NOCTTY
#include <termios.h> // termios structure
#include <errno.h>   // errno
#include <cstring>   // strerror

SerialPort::SerialPort() : connected(false), serial_fd(-1) {}

SerialPort::~SerialPort() {
    disconnect();
}

bool SerialPort::connect(const std::string& port, int baud_rate) {
    serial_fd = open(port.c_str(), O_RDWR | O_NOCTTY);
    if (serial_fd == -1) {
        std::cerr << "Error: Unable to open port " << port << " - " << strerror(errno) << std::endl;
        return false;
    }

    struct termios options;
    if (tcgetattr(serial_fd, &options) != 0) {
        std::cerr << "Error: Failed to get attributes for " << port << " - " << strerror(errno) << std::endl;
        disconnect();
        return false;
    }

    // Set baud rate
    speed_t baud;
    switch (baud_rate) {
        case 9600: baud = B9600; break;
        case 19200: baud = B19200; break;
        case 38400: baud = B38400; break;
        case 57600: baud = B57600; break;
        case 115200: baud = B115200; break;
        default:
            std::cerr << "Error: Unsupported baud rate " << baud_rate << std::endl;
            disconnect();
            return false;
    }

    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);

    // Set 8N1 mode
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Disable flow control
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_cflag |= CREAD | CLOCAL;

    // Raw input mode
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    // Apply settings
    if (tcsetattr(serial_fd, TCSANOW, &options) != 0) {
        std::cerr << "Error: Failed to set attributes for " << port << " - " << strerror(errno) << std::endl;
        disconnect();
        return false;
    }

    // Flush input & output buffers
    tcflush(serial_fd, TCIOFLUSH);

    connected = true;
    return true;
}

void SerialPort::disconnect() {
    if (connected) {
        close(serial_fd);
        serial_fd = -1;
        connected = false;
    }
}

bool SerialPort::send(const std::string& data) {
    if (!connected) {
        std::cerr << "Error: Port not connected\n";
        return false;
    }

    std::string data_with_crlf = data;
    if (data_with_crlf.back() != '\n') data_with_crlf += "\r\n";

    ssize_t bytes_written = write(serial_fd, data_with_crlf.c_str(), data_with_crlf.size());
    if (bytes_written < 0) {
        std::cerr << "Error: Failed to write to port - " << strerror(errno) << "\n";
        return false;
    }
    return true;
}

std::string SerialPort::receive() {
    if (!connected) {
        std::cerr << "Error: Port not connected\n";
        return "";
    }

    char buffer[1024];
    ssize_t bytes_read = read(serial_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        std::string data(buffer);

        // Remove CRLF
        if (data.size() > 1 && data[data.size() - 2] == '\r' && data[data.size() - 1] == '\n') {
            data = data.substr(0, data.size() - 2);
        }
        return data;
    } else if (bytes_read == 0) {
        std::cerr << "No data available to read\n";
    } else {
        std::cerr << "Error: Failed to read from port - " << strerror(errno) << "\n";
    }
    return "";
}

bool SerialPort::is_connected() const {
    return connected;
}
