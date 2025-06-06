#include "helpFunctions.h"
#include "Comands.h"

namespace wheatman {

    Polygon splitPolygon(const std::string& str)
    {
        Polygon polygon;
        std::istringstream in(str);
        size_t number;

        if (!(in >> number) || number < 3)
        {
            throw std::runtime_error("Incorrect input!");
        }
//        polygon.points.resize(number);
        for (size_t i = 0; i < number; ++i)
        {
            Point point;
            if(!(in>>point))
            {
                throw std::runtime_error("Error. Wrong coordinates!");
            }
            polygon.points.push_back(point);
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
            throw std::runtime_error("Error! Can't open file!");
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
            catch (const std::runtime_error& e)
            {
                continue;
            }
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
            if (polygonStr.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            try
            {
                Polygon figure = splitPolygon(polygonStr);
                echo(p, figure);
            }
            catch (const std::exception& e)
            {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if(commands == "INFRAME")
        {
            std::string polygonStr;
            std::getline(in, polygonStr);
            if (polygonStr.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            try
            {
                Polygon figure = splitPolygon(polygonStr);
                inframe(p, figure);
            }
            catch (const std::exception& e)
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
