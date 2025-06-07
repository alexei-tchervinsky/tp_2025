#include "Writer.hpp"

void Writer::write(std::ostream &out, const AVLDictionary &dict) const {
    dict.printAll(out);
}
