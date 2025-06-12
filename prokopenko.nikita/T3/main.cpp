#include "Commands.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  using namespace prokopenko;
  vector<Polygon> data;
  string command;

  while (cin >> command) {
    doCommand(command, data, cin);
  }

  return 0;
}
