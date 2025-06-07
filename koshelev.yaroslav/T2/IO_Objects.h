#ifndef IO_OBJECTS_H
#define IO_OBJECTS_H

#include <iosfwd>
#include "DataStruct.h"

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStruct(const DataStruct& a, const DataStruct& b);

#endif
