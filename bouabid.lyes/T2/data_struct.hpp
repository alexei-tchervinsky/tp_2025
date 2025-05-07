#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <regex>

struct DataStruct {
    double key1;
    char key2;
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

#endif // DATA_STRUCT_HPP
