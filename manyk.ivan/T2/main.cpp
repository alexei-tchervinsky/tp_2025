#include "DataStruct.hpp"
#include <limits>

int main() {
    std::vector<DataStruct> data;
    // while(!std::cin.eof())
    // {
    //     std::copy(
    //         std::istream_iterator<DataStruct>(std::cin),
    //         std::istream_iterator<DataStruct>(),
    //         std::back_inserter(data)
    //     );
    //     if(!std::cin)
    //     {
    //         std::cout<< "!cin" << '\n';
    //         std::cout <<std::hex << std::cin.flags() << std::boolalpha<< std::cin.fail() << std::cin.eof()<< '\n';
    //         std::cin.clear();
    //         std::cout <<std::hex << std::cin.flags() << std::boolalpha<< std::cin.fail() << std::cin.eof()<< '\n';
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     }
    // }
    while (!std::cin.eof()) {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );
        if (!std::cin.fail() || std::cin.eof()) {
            continue;
        }
        std::cin.clear();
    }
    std::sort(data.begin(), data.end(), compareData);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
