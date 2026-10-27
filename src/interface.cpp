#include "interface.h"
#include "errors.h"
#include <sstream>

Interface::Interface() : desc("Allowed options") {
    desc.add_options()
        ("help,h", "Show help")
        ("address,a", po::value<std::string>(&params.address)->required(), "Server address (required)")
        ("port,p",    po::value<uint16_t>(&params.port)->default_value(33333), "Server port (default 33333)")
        ("input,i",   po::value<std::string>(&params.inputFile)->required(), "Input data file (required)")
        ("output,o",  po::value<std::string>(&params.outputFile)->required(), "Output results file (required)")
        ("config,c",  po::value<std::string>(&params.configFile)->default_value("~/.config/vclient.conf"), "Auth config file");
}

bool Interface::Parser(int argc, const char** argv) {
    if (argc <= 1) return false;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    if (vm.count("help")) return false;
    po::notify(vm);
    return true;
}

std::string Interface::getDescription() {
    std::ostringstream ss;
    ss << desc;
    return ss.str();
}
