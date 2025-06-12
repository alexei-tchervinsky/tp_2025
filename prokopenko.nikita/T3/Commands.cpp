#include "Commands.hpp"
#include "iofmtguard.hpp"
#include <iomanip>
#include <limits>

namespace prokopenko {

  bool doCommand(const std::string& command, std::vector<Polygon>& data, std::istream& in) {
    if (command == "AREA") {
      size_t index;
      if (!(in >> index) || index >= data.size()) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      iofmtguard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1) << getArea(data[index]) << '\n';
      return true;
    }
    else if (command == "MAX") {
      if (data.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      size_t maxIndex = 0;
      double maxArea = getArea(data[0]);
      for (size_t i = 1; i < data.size(); ++i) {
        double currentArea = getArea(data[i]);
        if (currentArea > maxArea) {
          maxArea = currentArea;
          maxIndex = i;
        }
      }
      std::cout << maxIndex << '\n';
      return true;
    }
    else if (command == "MIN") {
      if (data.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      size_t minIndex = 0;
      double minArea = getArea(data[0]);
      for (size_t i = 1; i < data.size(); ++i) {
        double currentArea = getArea(data[i]);
        if (currentArea < minArea) {
          minArea = currentArea;
          minIndex = i;
        }
      }
      std::cout << minIndex << '\n';
      return true;
    }
    else if (command == "COUNT") {
      size_t sides;
      if (!(in >> sides)) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      size_t count = 0;
      for (const auto& p : data) {
        if (p.points.size() == sides) {
          ++count;
        }
      }
      std::cout << count << '\n';
      return true;
    }
    else if (command == "LESS") {
      double threshold;
      if (!(in >> threshold)) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      for (size_t i = 0; i < data.size(); ++i) {
        if (getArea(data[i]) < threshold) {
          std::cout << i << ' ';
        }
      }
      std::cout << '\n';
      return true;
    }
    else if (command == "ECHO") {
      Polygon p;
      if (!(in >> p)) {
        std::cout << "<INVALID COMMAND>\n";
        return true;
      }
      data.push_back(p);
      std::cout << p << '\n';
      return true;
    }

    return false;  // unknown command
  }

}
