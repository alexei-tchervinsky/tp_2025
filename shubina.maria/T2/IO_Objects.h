#pragma once

#include <vector>
#include <istream>
#include <ostream>
#include "DataStruct.h"

std::istream& operator>>(std::istream& is, DataStruct& ds);
std::ostream& operator<<(std::ostream& os, const DataStruct& ds);

extern std::vector<DataStruct> readDataStructs(std::istream& is);
extern void writeDataStructs(const std::vector<DataStruct>& data, std::ostream& os);

