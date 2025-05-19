#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include <iosfwd>
struct DataStruct
{
    double              key1  = 0.0;
    unsigned long long  key2  = 0ULL;
    std::string         key3  = {};
};
bool operator<(const DataStruct& lhs, const DataStruct& rhs);
std::istream& operator>>(std::istream& in,  DataStruct& ds);
std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
#endif
