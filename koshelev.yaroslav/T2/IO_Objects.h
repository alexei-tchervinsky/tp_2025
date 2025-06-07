#ifndef IO_OBJECTS_H
#define IO_OBJECTS_H

#include "DataStruct.h"
#include <iostream>

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
