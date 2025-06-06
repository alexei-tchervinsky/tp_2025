#ifndef READER_HPP
#define READER_HPP

#include <istream>
#include "AVLDictionary.hpp"

class Reader {
public:
    AVLDictionary read(std::istream& in, AVLDictionary& dict) const;

};

#endif
