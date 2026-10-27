#pragma once
#include <fstream>
#include <string>
#include <vector>

class DataWriter {
    std::ofstream f;
public:
    DataWriter() = delete;
    explicit DataWriter(const std::string& name);
    void write(const std::vector<double>& results);
    void close();
};
