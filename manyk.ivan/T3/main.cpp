#include "geometry.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong arguements\n";
        return -1;
    }

    std::ifstream in(argv[1]);
    std::vector<Polygon> polygons;
    while (!in.eof())
    {
        std::copy(std::istream_iterator<Polygon>{in}, std::istream_iterator<Polygon>{}, std::back_inserter(polygons));
        if (in.fail())
        {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::string a;
    while (std::cin >> a)
    {
        if (a == "RECTS")
        {
            Rects(polygons);
        }
        else if(a == "INTERSECTIONS")
        {
            Polygon target;
            std::cin >> target;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "<INVALID COMMAND>\n";
                continue;
            }
            std::size_t count = countIntersections(polygons, target);
            std::cout << count << "\n";
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
    return 0;
}
