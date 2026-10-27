#include "communicator.h"
#include "errors.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <memory>

namespace {
void chk(int rc, const char* fn) {
    if (rc == -1) throw NetworkError(std::string(fn) + ": " + std::strerror(errno));
}
}

Communicator::Communicator(const std::string& address, uint16_t port) {
    sock = ::socket(AF_INET, SOCK_STREAM, 0);
    chk(sock, "socket");
    timeval tv{180, 0};
    ::setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    std::unique_ptr<sockaddr_in> sa(new sockaddr_in{});
    sa->sin_family = AF_INET;
    sa->sin_port   = htons(port);
    sa->sin_addr.s_addr = inet_addr(address.c_str());
    if (sa->sin_addr.s_addr == INADDR_NONE) {
        ::close(sock); sock = -1;
        throw NetworkError("Communicator: bad address " + address);
    }
    int rc = ::connect(sock, reinterpret_cast<const sockaddr*>(sa.get()), sizeof(sockaddr_in));
    if (rc == -1) {
        int e = errno; ::close(sock); sock = -1;
        throw NetworkError(std::string("connect: ") + std::strerror(e));
    }
}

Communicator::~Communicator() { if (sock != -1) ::close(sock); }
void Communicator::close()    { if (sock != -1) { ::close(sock); sock = -1; } }

void Communicator::sendText(const std::string& s) {
    size_t sent = 0;
    while (sent < s.size()) {
        ssize_t rc = ::send(sock, s.data() + sent, s.size() - sent, 0);
        chk((int)rc, "send");
        sent += (size_t)rc;
    }
}

std::string Communicator::recvText() {
    char buf[16] = {0};
    ssize_t rc = ::recv(sock, buf, sizeof buf - 1, 0);
    chk((int)rc, "recv");
    return std::string(buf, (size_t)rc);
}

void Communicator::sendU32(uint32_t v) {
    chk((int)::send(sock, &v, sizeof v, 0), "send(u32)");
}

uint32_t Communicator::recvU32() {
    uint32_t n = 0;
    ssize_t rc = ::recv(sock, &n, sizeof n, 0);
    chk((int)rc, "recv(u32)");
    if (rc != sizeof n) throw NetworkError("recv(u32): short read");
    return n;
}

void Communicator::sendDoubles(const std::vector<double>& v) {
    size_t total = v.size() * sizeof(double), sent = 0;
    const char* p = reinterpret_cast<const char*>(v.data());
    while (sent < total) {
        ssize_t rc = ::send(sock, p + sent, total - sent, 0);
        chk((int)rc, "send(doubles)");
        sent += (size_t)rc;
    }
}

double Communicator::recvDouble() {
    double d = 0;
    ssize_t rc = ::recv(sock, &d, sizeof d, 0);
    chk((int)rc, "recv(double)");
    if (rc != sizeof d) throw NetworkError("recv(double): short read");
    return d;
}
