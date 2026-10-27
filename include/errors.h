#pragma once
#include <stdexcept>
#include <string>

class ProgramError : public std::runtime_error {
public: explicit ProgramError(const std::string& w) : std::runtime_error(w) {}
};
class InterfaceError : public ProgramError { public: using ProgramError::ProgramError; };
class IOError        : public ProgramError { public: using ProgramError::ProgramError; };
class AuthError      : public ProgramError { public: using ProgramError::ProgramError; };
class NetworkError   : public ProgramError { public: using ProgramError::ProgramError; };
