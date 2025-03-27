#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>

int main()
{
  std::vector<int> v{ 1, 2, 3 };
  std::ifstream in("data.txt");// в файле:4 5 6
  std::istream_iterator<int> beg(in);
  std::istream_iterator<int> end;
  auto ins = std::back_inserter(v);
  // ins имеет типstd::back_insert_iterator<std::vector<int>>
  while(!in.eof())
  {
    std::cout << *beg << '\n';
    *ins = *beg;
    ++beg;
// If the extraction fails, the object effectively replaces the stored pointer with a null pointer,
// thus making an end-of-sequence indicator.
    if (beg == end)
    {
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::istream_iterator<int> beg1(in);
      beg = beg1;
      continue;
    }
  }

  for (auto e : v)
  {
    std::cout << e << ',';
  }
  std::cout << '\n';
  return 0;
}