#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iosfwd>

namespace tarasenko {
    enum key_number { OCT = 1, CHAR = 2, STRING = 3 };

    struct DataStruct {
        unsigned long long key1;
        char key2;
        std::string key3;

        friend std::ostream& operator<<(std::ostream&, const DataStruct& src);
        friend std::istream& operator>>(std::istream&, DataStruct& dest);
    };

    bool DataStructSort(const DataStruct& dest1, const DataStruct& dest2);
}

#endif //DATASTRUCT_HPP
