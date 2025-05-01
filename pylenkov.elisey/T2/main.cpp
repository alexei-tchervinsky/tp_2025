#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct DataStruct
{
    char key1;
    unsigned long long key2;
    std::string key3;

    // перегруженный оператор ввода 
    friend std::istream& operator>>(std::istream& is, DataStruct& ds)
    {
        std::string line;
        if (!std::getline(is, line)) return is;

        size_t key1_start = line.find(":key1 '");
        if (key1_start != std::string::npos)
        {
            ds.key1 = line[key1_start + 7];
        }

        size_t key2_start = line.find(":key2 0x");
        if (key2_start != std::string::npos)
        {
            size_t key2_end = line.find(":", key2_start + 8);
            std::string hex_str = line.substr(key2_start + 8, key2_end - key2_start - 8);
            ds.key2 = std::stoull(hex_str, nullptr, 16);

        }

        size_t key3_start = line.find(":key3 \"");
        if (key3_start != std::string::npos)
        {
            size_t key3_end = line.find('"', key3_start + 7);
            ds.key3 = line.substr(key3_start + 7, key3_end - key3_start - 7);
        }

        return is; // чтобы поддерживать цепочку операций ввода
    }

    friend std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
    {
        os << "(:key1 '" << ds.key1 << "':key2 0x" << std::hex << std::uppercase << ds.key2 << std::nouppercase << ":key3 \"" << ds.key3 << "\":)";
        return os; // чтобы поддерживать цепочку операций вывода
    }
};

// собственный компаратор
bool compare(const DataStruct& a, const DataStruct& b) 
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}


int main() 
{
    std::vector<DataStruct> data;

    std::istream_iterator<DataStruct> start(std::cin), end;
    std::copy(start, end, std::back_inserter(data));

    std::sort(data.begin(), data.end(), compare);

    std::ostream_iterator<DataStruct> out(std::cout, "\n");
    std::copy(data.begin(), data.end(), out);
    return 0;
}
