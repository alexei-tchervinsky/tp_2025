#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>

struct DataStruct
{
    char key1;
    unsigned long long key2;
    std::string key3;

    friend std::istream& operator>>(std::istream& is, DataStruct& ds)
    {
        std::string line;
        if (!std::getline(is, line)) return is;

        // проверка key1
        size_t key1_start = line.find(":key1 '");
        if (key1_start == std::string::npos || key1_start + 8 > line.size())
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        ds.key1 = line[key1_start + 7];
        if (line[key1_start + 8] != '\'')
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        // проверка key2
        size_t key2_start = line.find(":key2 0x");
        if (key2_start == std::string::npos)
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        size_t key2_end = line.find(':', key2_start + 8);
        if (key2_end == std::string::npos)
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        std::string hex_str = line.substr(key2_start + 8, key2_end - (key2_start + 8));
        try
        {
            ds.key2 = std::stoull(hex_str, nullptr, 16);
        }
        catch (...)
        {
            is.setstate(std::ios::failbit);
            return is;
        }

        // проверка key3
        size_t key3_start = line.find(":key3 \"");
        if (key3_start == std::string::npos)
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        size_t key3_end = line.find('"', key3_start + 7);
        if (key3_end == std::string::npos)
        {
            is.setstate(std::ios::failbit);
            return is;
        }
        ds.key3 = line.substr(key3_start + 7, key3_end - (key3_start + 7));

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
    {
        return os << "(:key1 '" << ds.key1 << "':key2 0x"
                 << std::hex << std::uppercase << ds.key2 << std::nouppercase << std::dec
                 << ":key3 \"" << ds.key3 << "\":)";
    }
};

bool compare(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main()
{
    std::vector<DataStruct> data;
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        DataStruct ds;
        if (iss >> ds)
        {
            data.push_back(ds);
        }
    }

    std::sort(data.begin(), data.end(), compare);

    for (const auto& item : data)
    {
        std::cout << item << '\n';
    }

    return 0;
}
