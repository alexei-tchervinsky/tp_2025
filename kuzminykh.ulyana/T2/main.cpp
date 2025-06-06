#include "DataStructsIO.h"

int main()
{
    std::vector<DataStruct> data;

    try
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (data.empty())
        {
            return 0;
        }

        std::sort(data.begin(), data.end(), [](const DataStruct& a, const DataStruct& b)
            {
                if (a.key1 != b.key1) return a.key1 < b.key1;
                if (a.key2 != b.key2) return a.key2 < b.key2;
                return a.key3.length() < b.key3.length();
            });

        std::copy(
            data.begin(),
            data.end(),
            std::ostream_iterator<DataStruct>(std::cout, "\n")
        );
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
