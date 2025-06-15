#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // для std::all_of
#include "polygon.hpp"
#include "commands.hpp"

using namespace prokopenko;

int main(int argc, char* argv[]) {
  (void)argv;
  if (argc != 1) {
    std::cerr << "Unexpected arguments\n";
    return 1;
  }

  std::vector<Polygon> polys;
  Polygon p;
  while (std::cin >> p) {
    polys.push_back(p);
  }

  std::cin.clear(); // сброс флага EOF для последующего чтения команд
  std::string cmd;

  std::cout << "With data:\n";
  for (const auto& poly : polys) {
    std::cout << '\t' << poly << '\n';
  }

  while (std::cin >> cmd) {
    if (cmd == "COUNT") {
      std::string arg;
      if (!(std::cin >> arg)) {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }
      if (arg == "EVEN") CountEven(polys, std::cout);
      else if (arg == "ODD") CountOdd(polys, std::cout);
      else if (std::all_of(arg.begin(), arg.end(), ::isdigit)) {
        size_t n = std::stoul(arg);
        CountN(polys, std::cout, n);
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (cmd == "AREA") Area(polys, std::cout);
    else if (cmd == "MAX") Max(polys, std::cout);
    else if (cmd == "MIN") Min(polys, std::cout);
    else if (cmd == "MEAN") Mean(polys, std::cout);
    else if (cmd == "SAME") Same(polys, std::cout);
    else if (cmd == "RIGHT") Right(polys, std::cout);
    else if (cmd == "PERMS") Perms(polys, std::cout);
    else if (cmd == "LESS") Less(polys, std::cout);
    else if (cmd == "MORE") More(polys, std::cout);
    else if (cmd == "EQUAL") Equal(polys, std::cout);
    else if (cmd == "MAXSEQ") MaxSeq(polys, std::cout);
    else if (cmd == "RMECHO") RmEcho(polys, std::cout);
    else if (cmd == "ECHO") EchoCmd(polys, std::cout);
    else if (cmd == "LESSAREA") LessArea(polys, std::cout);
    else if (cmd == "INFRAME") InFrame(polys, std::cout);
    else if (cmd == "INTERSECTIONS") Intersections(polys, std::cout);
    else if (cmd == "RECTS") Rects(polys, std::cout);
    else if (cmd == "RIGHTSHAPES") RightShapes(polys, std::cout);
    else std::cout << "<INVALID COMMAND>\n";
  }

  return 0;
}
