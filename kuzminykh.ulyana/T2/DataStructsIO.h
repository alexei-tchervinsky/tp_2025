#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <limits>

namespace kuzminykh
{
    enum key_number { LongLong = 1, OCT = 2, STRING = 3 };

    struct DataStruct
    {
        long long key1_;
        unsigned long long key2_;

        std::string key3_;

        friend std::ostream& operator<<(std::ostream& out, const DataStruct& src);

        friend std::istream& operator>>(std::istream& in, DataStruct& dest);
    };

    bool compare(const DataStruct& a, const DataStruct& b);

    struct DelimiterIO
    {
        char delimiter;
    };

    struct LongLongIO
    {
        long long& ref;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct OctUnsignedLongLongIO
    {
        unsigned long long& ref;
    };


    struct LabelIO
    {
        std::string label;
    };

    std::istream& operator>>(std::istream&, LabelIO&&);
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, OctUnsignedLongLongIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);

    class iofmtguard {
    public:
        explicit iofmtguard(std::basic_ios<char>& s);

        iofmtguard(const iofmtguard& other) = delete;

        iofmtguard(iofmtguard&& other) noexcept = delete;

        iofmtguard& operator=(const iofmtguard& other) = delete;

        iofmtguard& operator=(iofmtguard&& other) noexcept = delete;

        ~iofmtguard();

    private:
        std::basic_ios<char>& s_;
        std::streamsize width_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };
}
