#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>

int main()
{
  std::vector<int> v{ 1, 2, 3 };
  // std::ifstream in("data.txt");// в файле:4 5 6
  std::istream_iterator<int> beg(std::cin);
  std::istream_iterator<int> end;
  auto ins = std::back_inserter(v);
  // ins имеет типstd::back_insert_iterator<std::vector<int>>
  while(!std::cin.eof())
  {
    std::copy(beg, end, ins);
    std::cout << *beg << '\n';
    if (std::cin.fail())
    // if (beg == end)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::istream_iterator<int> beg1(std::cin);
      beg = beg1;
      // continue;
    }
  }

  for (auto e : v)
  {
    std::cout << e << ',';
  }
  std::cout << '\n';
  return 0;
}