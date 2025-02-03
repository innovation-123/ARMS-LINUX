#ifndef PICKLE_WRITER_H
#define PICKLE_WRITER_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdint>

class PickleWriter {
private:
    std::ofstream file;

public:
    explicit PickleWriter(const std::string& filename);
    ~PickleWriter();

    void writeHeader();
    void writeString(const std::string& str);
    void writeFloat(float value);
    void writeMark();
    void writeList();
    void writeAppend();
    void writeEmptyList();
    void writeFloatArray(const std::vector<float>& arr);
    void writeDict();
    void writeSetItems();
    void writeFloatArrayDict(const std::map<std::string, std::vector<float>>& dict);
    void writeStop();
};

#endif
