#include "authenticator.h"
#include "errors.h"
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <fstream>

namespace CPP = CryptoPP;

Authenticator::Authenticator(const std::string& configPath) {
    std::ifstream f(configPath);
    if (!f) throw AuthError("Authenticator: cannot open config: " + configPath);
    std::string line;
    std::getline(f, line);
    auto pos = line.find(':');
    if (pos == std::string::npos) throw AuthError("Authenticator: bad config format: " + configPath);
    login    = line.substr(0, pos);
    password = line.substr(pos + 1);
    if (login.empty() || password.empty()) throw AuthError("Authenticator: empty login or password");
}

std::string Authenticator::makeSalt() {
    CPP::byte salt[8];
    CPP::AutoSeededRandomPool prng;
    prng.GenerateBlock(salt, sizeof salt);
    std::string s;
    CPP::ArraySource(salt, sizeof salt, true, new CPP::HexEncoder(new CPP::StringSink(s)));
    return s;
}

std::string Authenticator::makeHash(const std::string& salt16, const std::string& password) {
    CPP::SHA224 h;
    std::string out;
    CPP::StringSource(salt16 + password, true, new CPP::HashFilter(h, new CPP::HexEncoder(new CPP::StringSink(out))));
    return out;
}

std::string Authenticator::buildMessage() const {
    auto s = makeSalt();
    return login + s + makeHash(s, password);
}
