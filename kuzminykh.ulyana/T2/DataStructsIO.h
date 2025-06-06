#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iterator>

struct DataStruct
{
    long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;
};

struct DelimiterIO
{
    char exp;
};

struct LongLongIO
{
    long long& ref;
};

struct ULongLongOctIO
{
    unsigned long long& ref;
};

struct StringIO
{
    std::string& ref;
};

struct LabelIO
{
    std::string exp;
};

class iofmtguard
{
public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& d);
std::istream& operator>>(std::istream& in, LongLongIO&& d);
std::istream& operator>>(std::istream& in, ULongLongOctIO&& d);
std::istream& operator>>(std::istream& in, StringIO&& d);
std::istream& operator>>(std::istream& in, LabelIO&& d);
std::istream& operator>>(std::istream& in, DataStruct& d);

std::ostream& operator<<(std::ostream& out, const DataStruct& d);
