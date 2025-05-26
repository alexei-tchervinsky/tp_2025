#include "DataStruct.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

using namespace evdokimov;

int main() {
  std::vector<DataStruct> records;
  while (!std::cin.eof()) {
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(), std::back_inserter(records));
    if (!std::cin.fail()) {
      continue;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::sort(records.begin(), records.end(), sortByCriteria);
  std::copy(records.begin(), records.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
