#include "DataStruct.hpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <limits>
int main() {
    std::vector<popov::DataStruct> data;
    while(!std::cin.eof()) {
        popov::DataStruct temp;
        if(std::cin >> temp) data.push_back(temp);
        else {
            if(!std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
        }
    }
    std::sort(data.begin(),data.end(),popov::compare_structures);
    std::copy(data.begin(),data.end(),std::ostream_iterator<popov::DataStruct>(std::cout,"\n"));
    return 0;
}
