#pragma once
#include <string>
#include <cstdint>

struct Params {
    std::string address;
    uint16_t    port = 33333;
    std::string inputFile;
    std::string outputFile;
    std::string configFile;
};
