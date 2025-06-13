#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <functional>
#include <cctype>
#include <limits>
#include <algorithm>
#include "commands.hpp"
#include "polygon.hpp"

using namespace prokopenko;

static bool isNumber(const std::string& s) {
  if (s.empty()) return false;
  for (char c : s) {
    if (!std::isdigit(c)) return false;
  }
  return true;
}

static bool parsePolygonFromTokens(const std::vector<std::string>& toks,
  size_t& idx,
  Polygon& outPoly)
{
  if (idx >= toks.size()) return false;
  const std::string& ssz = toks[idx];
  if (!isNumber(ssz)) return false;
  size_t sz = 0;
  try {
    sz = std::stoul(ssz);
  }
  catch (...) {
    return false;
  }
  if (sz < 3) return false;
  if (idx + 1 + sz > toks.size()) return false;
  std::ostringstream oss;
  oss << sz;
  for (size_t i = 0; i < sz; ++i) {
    oss << ' ' << toks[idx + 1 + i];
  }
  std::istringstream iss(oss.str());
  Polygon p;
  if (!(iss >> p)) {
    return false;
  }
  outPoly = std::move(p);
  idx += 1 + sz;
  return true;
}

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "Error: file cannot be opened\n";
    return 1;
  }

  std::vector<std::string> commandsQueue;
  {
    std::string tok;
    while (std::cin >> tok) {
      commandsQueue.push_back(tok);
    }
  }
  size_t cmdIdx = 0;

  std::string line;
  std::vector<std::string> blockLines;

  auto processBlock = [&](const std::vector<std::string>& lines) {
    std::vector<Polygon> polys;
    for (const auto& ln : lines) {
      std::istringstream iss(ln);
      Polygon p;
      if (iss >> p) {
        polys.push_back(std::move(p));
      }
    }
    if (cmdIdx >= commandsQueue.size()) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    const std::string cmd = commandsQueue[cmdIdx++];
    if (cmd == "COUNT") {
      if (cmdIdx >= commandsQueue.size()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
      const std::string param = commandsQueue[cmdIdx++];
      if (param == "ODD") {
        CountOdd(polys, std::cout);
      }
      else if (param == "EVEN") {
        CountEven(polys, std::cout);
      }
      else if (isNumber(param)) {
        size_t n = 0;
        try {
          n = std::stoul(param);
        }
        catch (...) {
          std::cout << "<INVALID COMMAND>\n";
          return;
        }
        CountN(polys, std::cout, n);
      }
      else {
        std::cout << "<INVALID COMMAND>\n";
      }
      return;
    }
    static const std::map<std::string,
      std::function<void(const std::vector<Polygon>&, std::ostream&)>> cmap = {
      {"AREA", Area},
      {"MAX", Max},
      {"MIN", Min},
      {"MEAN", Mean},
      {"SAME", Same},
      {"RIGHT", Right},
      {"PERMS", Perms},
      {"LESS", Less},
      {"MORE", More},
      {"EQUAL", Equal}
    };
    auto it = cmap.find(cmd);
    if (it == cmap.end()) {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    it->second(polys, std::cout);
    };

  while (std::getline(infile, line)) {
    if (line.empty()) {
      processBlock(blockLines);
      blockLines.clear();
    }
    else {
      blockLines.push_back(line);
    }
  }
  if (!blockLines.empty()) {
    processBlock(blockLines);
    blockLines.clear();
  }
  // лишние команды
  while (cmdIdx < commandsQueue.size()) {
    std::cout << "<INVALID COMMAND>\n";
    ++cmdIdx;
  }
  return 0;
}
