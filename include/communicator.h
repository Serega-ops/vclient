#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Communicator {
    int sock = -1;
public:
    Communicator() = delete;
    Communicator(const std::string& address, uint16_t port);
    ~Communicator();
    void close();
    void sendText(const std::string& s);
    std::string recvText();
    void     sendU32(uint32_t v);
    uint32_t recvU32();
    void     sendDoubles(const std::vector<double>& v);
    double   recvDouble();
};
