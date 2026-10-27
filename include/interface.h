#pragma once
#include <boost/program_options.hpp>
#include <string>
#include "params.h"

namespace po = boost::program_options;

class Interface {
private:
    po::options_description desc;
    po::variables_map vm;
    Params params;
public:
    Interface();
    bool Parser(int argc, const char** argv);
    std::string getDescription();
    Params getParams() const { return params; }
};
