#include "data_reader.h"
#include "errors.h"
#include <cstdint>

DataReader::DataReader(const std::string& name) {
    f.exceptions(std::ios::failbit | std::ios::badbit);
    try { f.open(name); }
    catch (const std::ios_base::failure& e) {
        throw IOError("DataReader::open(" + name + "): " + e.what());
    }
}

DataVectors DataReader::read() {
    try {
        uint32_t count = 0;
        f >> count;
        DataVectors out;
        out.reserve(count);
        for (uint32_t i = 0; i < count; ++i) {
            uint32_t size = 0;
            f >> size;
            std::vector<double> v(size);
            for (uint32_t j = 0; j < size; ++j) f >> v[j];
            out.push_back(std::move(v));
        }
        return out;
    } catch (const std::ios_base::failure& e) {
        throw IOError(std::string("DataReader::read: ") + e.what());
    }
}
