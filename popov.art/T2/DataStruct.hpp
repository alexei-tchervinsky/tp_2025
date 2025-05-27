#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <iostream>
#include <string>
#include <utility>
namespace popov {
struct DataStruct {
    char key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};
struct DelimiterIO { char exp; };
struct RationalIO { std::pair<long long, unsigned long long>& ref; };
struct CharIO { char& ref; };
struct StringIO { std::string& ref; };
struct LabelIO { std::string exp; };
class iofmtguard {
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
std::istream& operator>>(std::istream& in, RationalIO&& dest);
std::istream& operator>>(std::istream& in, CharIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
bool compare_structures(const DataStruct& a, const DataStruct& b);
}
#endif
