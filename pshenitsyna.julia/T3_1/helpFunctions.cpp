#include "helpFunctions.h"
#include "Comands.h"

namespace wheatman {

    Polygon splitPolygon(const std::string& str)
    {
        Polygon polygon;
        std::istringstream in(str);
        size_t number;
        in >> number;

        if (in.fail() || number < 3)
        {
            throw std::runtime_error("Incorrect input!");
        }
        polygon.points.resize(number);
        for (size_t i = 0; i < number; ++i)
        {
            if(!(in>>polygon.points[i]))
            {
                throw std::runtime_error("Error. Wrong coordinates!");
            }
            in >> polygon.points[i];
        }

        std::string remaining;
        if (in >> remaining && !remaining.empty()) {
            throw std::runtime_error("Error. Too much points!");
        }
        return polygon;
    }

    std::vector<Polygon> readFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Open file error!\n";
            exit(1);
        }

        std::vector<Polygon> polygons;
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || std::all_of(line.begin(), line.end(), [](unsigned char c){ return std::isspace(c); }))
            {
                continue;
            }
            try
            {
                Polygon polygon = wheatman::splitPolygon(line);
                polygons.push_back(polygon);
            }
            catch (const std::runtime_error& e){}
        }
        file.close();
        return polygons;
    }
    void CommandsHandler (const std::string& command, std::vector<Polygon>& p)
    {
        std::stringstream in(command);
        std::string commands;
        in >> commands;

        if(commands == "AREA")
        {
            std::string parameter;
            in >> parameter;
            area(p, parameter);
        }
        else if(commands == "MAX")
        {
            std::string parameter;
            in >> parameter;
            max(p, parameter);
        }
        else if(commands == "MIN")
        {
            std::string parameter;
            in >> parameter;
            min(p, parameter);
        }
        else if(commands == "COUNT")
        {
            std::string parameter;
            in >> parameter;
            count(p, parameter);
        }
        else if(commands == "ECHO")
        {
            std::string polygonStr;
            std::getline(in, polygonStr);
            try
            {
                Polygon figure = splitPolygon(polygonStr);
                echo(p, figure);
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if(commands == "INFRAME")
        {
            std::string polygonStr;
            std::getline(in, polygonStr);
            try
            {
                Polygon figure = splitPolygon(polygonStr);
                inframe(p, figure);
            }
            catch (...)
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else
        {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
