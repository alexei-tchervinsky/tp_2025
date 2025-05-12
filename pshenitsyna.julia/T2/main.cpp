/*
 * T2 key 1: ULL OCT
 * T2 key 2" CHR LIT
 * (:key1 10ull:key2 'c':key3 "Data":)
 */
#include "DataStruct.h"
#include "DataStructSort.h"

#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

int main() {
    std::vector<DataStruct> v;
    while (!std::cin.eof())
    {
        DataStruct ds;
        if (std::cin >> ds)
        {
            v.push_back(ds);
        }
        else if (!std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::sort(v.begin(), v.end(), DataStructSort);
    std::copy(
            v.begin(),
            v.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
