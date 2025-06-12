#ifndef IO_OBJECTS_H
#define IO_OBJECTS_H

#include <vector>
#include "DataStruct.h"

namespace solution {
    void readData(std::istream& in, std::vector<DataStruct>& data);
    void sortData(std::vector<DataStruct>& data);
    void writeData(std::ostream& out, const std::vector<DataStruct>& data);
}

#endif
