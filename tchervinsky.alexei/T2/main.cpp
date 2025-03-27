#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include "stream_guard.hpp"


struct DataStruct
{
  int i;
};

std::istream & operator >> (std::istream & in, DataStruct & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct temp;
  in >> std::skipws >> temp.i;
  if (!in)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest = temp;
  return in;
}

std::ostream & operator << (std::ostream & out, const DataStruct & data)
{
  StreamGuard guard(out);
  out << data.i;
  return out;
}

int main()
{
  std::vector<DataStruct> v;
  while(!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(v));
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  for (auto e : v)
  {
    std::cout << e << ',';
  }
  std::cout << '\n';

  return 0;
}