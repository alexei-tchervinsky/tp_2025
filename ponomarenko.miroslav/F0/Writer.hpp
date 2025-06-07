#ifndef WRITER_HPP
#define WRITER_HPP

#include <ostream>
#include "AVLDictionary.hpp"

class Writer {
public:
    void write(std::ostream& out, const AVLDictionary& dict) const;
};

#endif
