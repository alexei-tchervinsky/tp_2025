#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>

struct DataStruct {
    double key1;
    unsigned long long key2;
    std::string key3;
};

bool parseScientificDouble(const std::string& str, double& value);
bool parseHexULL(const std::string& str, unsigned long long& value);

#endif
