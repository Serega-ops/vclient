#include "data_writer.h"
#include "errors.h"
#include <cstdint>

DataWriter::DataWriter(const std::string& name) {
    f.exceptions(std::ios::failbit | std::ios::badbit);
    try { f.open(name, std::ios::binary | std::ios::trunc); }
    catch (const std::ios_base::failure& e) {
        throw IOError("DataWriter::open(" + name + "): " + e.what());
    }
}

void DataWriter::write(const std::vector<double>& results) {
    try {
        uint32_t n = static_cast<uint32_t>(results.size());
        f.write(reinterpret_cast<const char*>(&n), sizeof n);
        if (n) f.write(reinterpret_cast<const char*>(results.data()), static_cast<std::streamsize>(n * sizeof(double)));
    } catch (const std::ios_base::failure& e) {
        throw IOError(std::string("DataWriter::write: ") + e.what());
    }
}

void DataWriter::close() {
    try { f.close(); }
    catch (const std::ios_base::failure& e) {
        throw IOError(std::string("DataWriter::close: ") + e.what());
    }
}
