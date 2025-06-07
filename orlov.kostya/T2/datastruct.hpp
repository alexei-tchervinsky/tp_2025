#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace orlov
{
    struct DataStruct
    {
        unsigned long long key1{0};
        double key2{0.0};
        std::string key3{};

        DataStruct() = default;
        DataStruct(unsigned long long k1, double k2, std::string k3) :
            key1(k1), key2(k2), key3(std::move(k3)) {}

        friend std::ostream& operator<<(std::ostream& os, const DataStruct& src);
        friend std::istream& operator>>(std::istream& is, DataStruct& src);
    };

    bool compareDataStruct(const DataStruct& first, const DataStruct& second);
}

#endif // !__DATASTRUCT_HPP

