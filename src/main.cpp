#include <iostream>
#include "interface.h"
#include "data_reader.h"
#include "data_writer.h"
#include "authenticator.h"
#include "communicator.h"
#include "errors.h"
#include <boost/program_options.hpp>

int main(int argc, const char** argv) {
    try {
        Interface ui;
        if (!ui.Parser(argc, argv)) {
            std::cout << ui.getDescription();
            return 0;
        }
        Params p = ui.getParams();
        DataReader reader(p.inputFile);
        DataVectors vectors = reader.read();
        Communicator comm(p.address, p.port);
        Authenticator auth(p.configFile);
        comm.sendText(auth.buildMessage());
        std::string answer = comm.recvText();
        if (answer.rfind("OK", 0) != 0) throw AuthError("server rejected: " + answer);
        comm.sendU32((uint32_t)vectors.size());
        std::vector<double> results;
        results.reserve(vectors.size());
        for (const auto& v : vectors) {
            comm.sendU32((uint32_t)v.size());
            comm.sendDoubles(v);
            results.push_back(comm.recvDouble());
        }
        comm.close();
        DataWriter w(p.outputFile);
        w.write(results);
        w.close();
        return 0;
    }
    catch (const boost::program_options::error& e) {
        std::cerr << "Interface error: " << e.what() << "\nUse -h for help\n";
        return 1;
    }
    catch (const ProgramError& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 2;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 3;
    }
}
