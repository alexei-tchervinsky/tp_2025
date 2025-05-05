#ifndef T2_OBJECTSIO_H
#define T2_OBJECTSIO_H
#include <iostream>

struct OctIO{
    unsigned long long& ref; //для key1
};

struct DelimiterIO{
    char exp; //для разделителей
};

struct LabelIO{
    std::string exp; //для ключевого слова key
};

struct CharIO{
    char& ref; //для key2
};

struct StringIO{
    std::string& ref; //для key3
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, OctIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, CharIO&& dest);

#endif //T2_OBJECTSIO_H
