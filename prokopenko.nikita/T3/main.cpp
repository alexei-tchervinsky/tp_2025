#include <fstream>
#include <iostream>
#include <vector>
#include "Polygon.hpp"
#include "Commands.hpp"

int main(int argc, char* argv[]) {
  if (argc != 2) return 1;
  std::ifstream f(argv[1]);
  if (!f) return 1;

  std::vector<prokopenko::Polygon> v;
  prokopenko::Polygon p;
  while (f >> p) v.push_back(p);

  std::string cmd;
  while (std::cin >> cmd) {
    prokopenko::doCommand(cmd, v, std::cin);
  }

  return 0;
}
