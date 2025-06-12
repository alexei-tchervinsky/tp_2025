#include "IO_Objects.h"
#include <algorithm>

namespace solution {

  void readData(std::istream& in, std::vector<DataStruct>& data) {
    DataStruct item;
    while (in >> item) {
      data.push_back(item);
    }
  }

  void sortData(std::vector<DataStruct>& data) {
    std::sort(data.begin(), data.end());
  }

  void writeData(std::ostream& out, const std::vector<DataStruct>& data) {
    for (const auto& item : data) {
      out << item << '\n';
    }
  }

}
