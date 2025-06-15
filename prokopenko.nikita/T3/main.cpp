#include "polygon.hpp"
#include "commands.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // ← добавлено для std::all_of

using namespace prokopenko;

int main() {
  std::vector<Polygon> polys;
  std::string cmd;

  while (std::cin >> cmd) {
    if (cmd == "ECHO") {
      Polygon p;
      if (std::cin >> p) {
        polys.push_back(p);
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::string skip;
        std::getline(std::cin, skip);
      }
    }
    else if (cmd == "COUNT") {
      std::string param;
      if (!(std::cin >> param)) {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      if (param == "ODD") CountOdd(polys, std::cout);
      else if (param == "EVEN") CountEven(polys, std::cout);
      else if (std::all_of(param.begin(), param.end(), ::isdigit)) {
        size_t n = std::stoul(param);
        CountN(polys, std::cout, n);
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (cmd == "AREA") {
      Area(polys, std::cout);
    }
    else if (cmd == "MAX") {
      Max(polys, std::cout);
    }
    else if (cmd == "MIN") {
      Min(polys, std::cout);
    }
    else if (cmd == "MEAN") {
      Mean(polys, std::cout);
    }
    else if (cmd == "SAME") {
      Same(polys, std::cout);
    }
    else if (cmd == "RIGHT") {
      Right(polys, std::cout);
    }
    else if (cmd == "PERMS") {
      Perms(polys, std::cout);
    }
    else if (cmd == "LESS") {
      Less(polys, std::cout);
    }
    else if (cmd == "MORE") {
      More(polys, std::cout);
    }
    else if (cmd == "EQUAL") {
      Equal(polys, std::cout);
    }
    else if (cmd == "MAXSEQ") {
      MaxSeq(polys, std::cout);
    }
    else if (cmd == "RMECHO") {
      RmEcho(polys, std::cout);
    }
    else if (cmd == "LESSAREA") {
      LessArea(polys, std::cout);
    }
    else if (cmd == "INFRAME") {
      InFrame(polys, std::cout);
    }
    else if (cmd == "INTERSECTIONS") {
      Intersections(polys, std::cout);
    }
    else if (cmd == "RECTS") {
      Rects(polys, std::cout);
    }
    else if (cmd == "RIGHTSHAPES") {
      RightShapes(polys, std::cout);
    }
    else {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
