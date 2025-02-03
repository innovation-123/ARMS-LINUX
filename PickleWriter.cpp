#include "PickleWriter.h"
#include <stdexcept>
#include <cstring>

PickleWriter::PickleWriter(const std::string& filename) {
    file.open(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
}

PickleWriter::~PickleWriter() {
    if (file.is_open()) {
        file.close();
    }
}

void PickleWriter::writeHeader() {
    file.put('\x80');
    file.put('\x02');
}

void PickleWriter::writeString(const std::string& str) {
    file.put('U');
    uint8_t len = static_cast<uint8_t>(str.length());
    file.put(static_cast<char>(len));
    file.write(str.c_str(), len);
}

void PickleWriter::writeFloat(float value) {
    file.put('G');
    char bytes[8];
    uint64_t bits;
    double dval = static_cast<double>(value);
    memcpy(&bits, &dval, 8);
    for (int i = 7; i >= 0; i--) {
        bytes[7 - i] = (bits >> (i * 8)) & 0xFF;
    }
    file.write(bytes, 8);
}

void PickleWriter::writeMark() {
    file.put('(');
}

void PickleWriter::writeList() {
    file.put('l');
}

void PickleWriter::writeAppend() {
    file.put('a');
}

void PickleWriter::writeEmptyList() {
    file.put(']');
}

void PickleWriter::writeFloatArray(const std::vector<float>& arr) {
    writeEmptyList();
    for (float value : arr) {
        writeFloat(value);
        writeAppend();
    }
}

void PickleWriter::writeDict() {
    file.put('d');
}

void PickleWriter::writeSetItems() {
    file.put('u');
}

void PickleWriter::writeFloatArrayDict(const std::map<std::string, std::vector<float>>& dict) {
    file.put('}');
    if (!dict.empty()) {
        writeMark();
        for (const auto& pair : dict) {
            writeString(pair.first);
            writeFloatArray(pair.second);
        }
        writeSetItems();
    }
}

void PickleWriter::writeStop() {
    file.put('.');
}
