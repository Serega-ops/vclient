#pragma once
#include <string>

class Authenticator {
    std::string login;
    std::string password;
public:
    Authenticator() = delete;
    explicit Authenticator(const std::string& configPath);
    const std::string& getLogin() const { return login; }
    static std::string makeSalt();
    static std::string makeHash(const std::string& salt16, const std::string& password);
    std::string buildMessage() const;
};
