#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

int main()
{
  std::vector<int> v{ 1, 2, 3 };
  std::ifstream in("data.txt");// в файле:4 5 6
  std::istream_iterator<int> beg(in);
  std::istream_iterator<int> end;
  auto ins = std::back_inserter(v);
  // ins имеет типstd::back_insert_iterator<std::vector<int>>
  while (beg != end) {
    *ins = *beg;
    ++beg;
    ++ins;// не имеет эффекта
  }

  for (auto e : v)
  {
    std::cout << e << ',';
  }
  std::cout << '\n';
  return 0;
}