#include "geometry.hpp"
#include <map>
#include <functional>

void rectsCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);
void intersectionsCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);
void areaCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);
void maxCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);
void minCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);
void countCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream&);

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
           // std::cout << 1;
        }
    }
    // for(auto &i : polygons) {
    //         std::cout << i << std::endl;
    //     }
    // std::string a;
    // while (std::cin >> a)
    // {
    //     if (a == "RECTS")
    //     {
    //         Rects(polygons);
    //     }
    //     else if(a == "INTERSECTIONS")
    //     {
    //         Polygon target;
    //         std::cin >> target;
    //         if (std::cin.fail())
    //         {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             std::cout << "<INVALID COMMAND>\n";
    //             continue;
    //         }
    //         std::size_t count = countIntersections(polygons, target);
    //         std::cout << count << "\n";
    //     }
    //     else if (a == "AREA")
    //     {
    //         std::string arg;
    //         if (std::cin >> arg)
    //             areaCommand(polygons, arg);
    //         else
    //         {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             std::cout << "<INVALID COMMAND>\n";
    //             continue;
    //         }
    //     }
    //     else if (a == "MAX") {
    //         std::string arg;
    //         if (std::cin >> arg)
    //             maxCommand(polygons, arg);
    //         else {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             std::cout << "<INVALID COMMAND>\n";
    //             continue;
    //         }
    //     }
    //     else if (a == "MIN") {
    //         std::string arg;
    //         if (std::cin >> arg)
    //             minCommand(polygons, arg);
    //         else
    //         {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             std::cout << "<INVALID COMMAND>\n";
    //             continue;
    //         }
    //     }
    //      else if (a == "COUNT") {
    //         std::string arg;
    //         if (std::cin >> arg) {
    //             if (arg == "ODD") {
    //                 countOdd(polygons);
    //             }
    //             else if (arg == "EVEN") {
    //                 countEven(polygons);
    //             }
    //             else {
    //                 try {
    //                     int num = std::stoi(arg);
    //                     if (num < 3) {
    //                         std::cout << "<INVALID COMMAND>\n";
    //                     }
    //                     countNum(polygons, num);
    //                 }
    //                 catch (...) {
    //                     std::cin.clear();
    //                     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //                     std::cout << "<INVALID COMMAND>\n";
    //                 }
    //             }
    //         }
    //         else {
    //             std::cin.clear();
    //             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //             std::cout << "<INVALID COMMAND>\n";
    //         }
    //     }
    //     else
    //     {
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "<INVALID COMMAND>\n";
    //     }
    // }
    std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
        using CommandFunc = void (*)(const std::vector<Polygon>&, std::istream&, std::ostream&);
        using namespace std::placeholders;
        commands["RECTS"] = std::bind(rectsCommand, std::cref(polygons), _1, _2);
        commands["INTERSECTIONS"] = std::bind(intersectionsCommand, std::cref(polygons), _1, _2);
        commands["AREA"] = std::bind(static_cast<CommandFunc>(areaCommand), std::cref(polygons), _1, _2);
        commands["MAX"] = std::bind(static_cast<CommandFunc>(maxCommand), std::cref(polygons), _1, _2);
        commands["MIN"] = std::bind(static_cast<CommandFunc>(minCommand), std::cref(polygons), _1, _2);
        commands["COUNT"] = std::bind(countCommand, std::cref(polygons), _1, _2);
    }
    std::string cmd = "";
    while (std::cin >> cmd)
    {
        try
        {
            commands.at(cmd)(std::cin, std::cout);
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    return 0;
}

void rectsCommand(const std::vector<Polygon>& polygons, std::istream&, std::ostream& out)
{
    size_t count = std::count_if(polygons.begin(), polygons.end(), isRectangle);
    out << count << "\n";
}

void intersectionsCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
    Polygon target;
    if (in >> target) {
        size_t count = countIntersections(polygons, target);
        out << count << "\n";
    } else {
        out << "<INVALID COMMAND>\n";
    }
}

void areaCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out) {
    std::string arg;
    if (in >> arg) {
        if (arg == "EVEN") {
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double acc, const Polygon& p) {
                    return (p.points.size() % 2 == 0) ? acc + computeArea(p) : acc;
                });
            out << std::fixed << std::setprecision(1) << sum << "\n";
        }
        else if (arg == "ODD")
        {
            double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double current_sum, const Polygon& poly) {
                    if (poly.points.size() % 2 == 1) {
                        return current_sum + computeArea(poly);
                    }
                    return current_sum;
                });
            out << std::fixed << std::setprecision(1) << sum << "\n";
        }
        else if (arg == "MEAN")
        {
            if (polygons.empty())
            {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                [](double current_sum, const Polygon& poly) {
                    if (poly.points.size() % 2 == 1) {
                        return current_sum + computeArea(poly);
                    }
                    return current_sum;
                });
            out << std::fixed << std::setprecision(1) << total / polygons.size() << "\n";
        }
        else {
            try
            {
                size_t num = std::stoul(arg);
                if (num <= 2)
                {
                    std::cout << "<INVALID COMMAND>\n";
                    return;
                }
                double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
                    [num](double current_sum, const Polygon& poly) {
                        if (poly.points.size() == num){
                            return current_sum + computeArea(poly);
                        }
                        return current_sum;
                });
                out << std::fixed << std::setprecision(1) << sum << "\n";
            } catch (...) {
                out << "<INVALID COMMAND>\n";
            }
        }
    } else {
        out << "<INVALID COMMAND>\n";
    }
}

void maxCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    std::string arg;
    if (polygons.empty())
    {
        out << "<INVALID COMMAND>\n";
        return;
    }
    in >> arg;
    if (arg == "AREA")
    {
        auto max_it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return computeArea(a) < computeArea(b);
            });
        out << std::fixed << std::setprecision(1) << computeArea(*max_it) << "\n";
    }
    else if (arg == "VERTEXES")
    {
        auto max_it = std::max_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        out << max_it->points.size() << "\n";
    }
    else
    {
        out << "<INVALID COMMAND>\n";
    }
}

void minCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    std::string arg;
    if (polygons.empty())
    {
        out << "<INVALID COMMAND>\n";
        return;
    }
    in >> arg;
    if (arg == "AREA")
    {
        auto min_it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return computeArea(a) < computeArea(b);
            });
        out << std::fixed << std::setprecision(1) << computeArea(*min_it) << "\n";
    }
    else if (arg == "VERTEXES")
    {
        auto min_it = std::min_element(polygons.begin(), polygons.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            });
        out << min_it->points.size() << "\n";
    }
    else {
        out << "<INVALID COMMAND>\n";
    }
}

void countCommand(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
    std::string arg;
    if (polygons.empty())
    {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }
    in >> arg;
    if (arg == "EVEN")
    {
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [](const auto& poly) {
                return poly.points.size() % 2 == 0;
            });
        out << count << '\n';
    }

    else if (arg == "ODD")
    {
        size_t count = std::count_if(polygons.begin(), polygons.end(),
            [](const auto& poly) {
                return poly.points.size() % 2 == 1;
            });
        out << count << '\n';
    }

    else
    {
        try{
            int num = std::stoi(arg);
            if (num < 3) {
                out << "<INVALID COMMAND>\n";
                return;
            }
            else{
                std::size_t count = std::count_if(polygons.begin(), polygons.end(), [num](const Polygon& poly) {
                    return static_cast<int>(poly.points.size()) == num;
                    });
                out << count << '\n';
            }
        }
        catch(...)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
