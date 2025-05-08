#include "DataStructSort.h"

bool DataStructSort(const DataStruct& dest1, const DataStruct& dest2)
{
    if (dest1.key1 != dest2.key1)
    {
        return dest1.key1 < dest2.key1;
    }
    if (dest1.key2 != dest2.key2)
    {
        return dest1.key2 < dest2.key2;
    }
    return dest1.key3.length() < dest2.key3.length();
}
