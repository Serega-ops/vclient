#pragma once
#include <fstream>
#include <string>
#include <vector>

using DataVectors = std::vector<std::vector<double>>;

class DataReader {
    std::ifstream f;
public:
    DataReader() = delete;
    explicit DataReader(const std::string& name);
    DataVectors read();
};
