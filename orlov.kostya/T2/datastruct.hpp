#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>

namespace orlov
{
    struct DataStruct
    {
        unsigned long long key1;
        double key2;
        std::string key3;

        friend std::ostream& operator<<
        (
            std::ostream& os,
            const DataStruct& src
        );
        friend std::istream& operator>>(std::istream& is, DataStruct& src);
    };

    bool compareDataStruct(const DataStruct& first, const DataStruct& second)
}

#endif // !__DATASTRUCT_HPP