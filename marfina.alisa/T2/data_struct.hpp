#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <utility>
#include <string>

namespace marfina
{
struct DataStruct
{
    std::pair<long long, unsigned long long> key1;
    char key2;
    std::string key3;
};

struct DelimiterIO
{
    char exp;
};

struct RationalIO
{
    std::pair<long long, unsigned long long>& ref;
};

struct CharIO
{
    char& ref;
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
    explicit iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
private:
    std::basic_ios<char>& s_;
    std::streamsize width_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
};

std::acceptable_format& operator>>(std::acceptable_format& in, DelimiterIO&& dest);
std::acceptable_format& operator>>(std::acceptable_format& in, RationalIO&& dest);
std::acceptable_format& operator>>(std::acceptable_format& in, CharIO&& dest);
std::acceptable_format& operator>>(std::acceptable_format& in, StringIO&& dest);
std::acceptable_format& operator>>(std::acceptable_format& in, LabelIO&& dest);
std::acceptable_format& operator>>(std::acceptable_format& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

bool compare_structures(const DataStruct& a, const DataStruct& b);
bool acceptable_format(const DataStruct& ds);

}

#endif
