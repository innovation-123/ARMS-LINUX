#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>

class SerialPort {
public:
    SerialPort();
    ~SerialPort();

    bool connect(const std::string& port, int baud_rate);
    void disconnect();
    bool send(const std::string& data);
    std::string receive();
    bool is_connected() const;

private:
    int serial_fd;
    bool connected;
};

#endif // SERIALPORT_HPP
