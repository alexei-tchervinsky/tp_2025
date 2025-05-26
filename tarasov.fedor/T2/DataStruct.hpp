#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include <limits>

namespace tarasov {
    struct DataStruct {
        double key1;
        char key2;
        std::string key3;

        bool operator<(const DataStruct& other) const;
    };

    std::istream& operator>>(std::istream& in, DataStruct& dest);

    std::ostream& operator<<(std::ostream& out, const DataStruct& data);

    std::string formatScientific(double data);
}

#endif
