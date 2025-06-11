#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <iterator>
#include <iostream>
#include <string>

namespace shubina
{
struct DataStruct
{
    char key1;
    unsigned long long key2;  // Изменено с pair<long long, unsigned long long>
    std::string key3;
};

struct DelimiterIO { char exp; };
struct UnsignedLongLongIO { unsigned long long& ref; };  // Замена RationalIO
struct CharIO { char& ref; };
struct StringIO { std::string& ref; };
struct LabelIO { std::string exp; };

class iofmtguard
{
public:
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
std::istream& operator>>(std::istream& in, CharIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

bool compare_structures(const DataStruct& a, const DataStruct& b);
}
#endif

