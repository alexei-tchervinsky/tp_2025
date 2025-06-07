#include "helpFunctions.h"
#include "Comands.h"
#include <functional>
#include <map>

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
    std::map<std::string, std::function<void(std::stringstream&)>> commandMap;

    void initializeCommands (std::vector<Polygon>& p)
    {
        commandMap["AREA"] = [&p](std::stringstream& in) {
            std::string param; in >> param;
            area(p, param);
        };

        commandMap["COUNT"] = [&p](std::stringstream& in) {
            std::string param; in >> param;
            count(p, param);
        };

        commandMap["MAX"] = [&p](std::stringstream& in) {
            std::string param; in >> param;
            max(p, param);
        };

        commandMap["MIN"] = [&p](std::stringstream& in) {
            std::string param; in >> param;
            min(p, param);
        };

        commandMap["ECHO"] = [&p](std::stringstream& in) {
            std::string rest;
            std::getline(in, rest);
            if (rest.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            try {
                Polygon figure = splitPolygon(rest);
                echo(p, figure);
            } catch (...) {
                std::cout << "<INVALID COMMAND>\n";
            }
        };

        commandMap["INFRAME"] = [&p](std::stringstream& in) {
            std::string rest;
            std::getline(in, rest);
            if (rest.empty()) {
                std::cout << "<INVALID COMMAND>\n";
                return;
            }
            try {
                Polygon figure = splitPolygon(rest);
                inframe(p, figure);
            } catch (...) {
                std::cout << "<INVALID COMMAND>\n";
            }
        };
    }
    void CommandsHandler(const std::string& command, std::vector<Polygon>& p) {
        std::stringstream in(command);
        std::string cmd;
        in >> cmd;

        auto it = commandMap.find(cmd);
        if (it != commandMap.end()) {
            it->second(in);  // вызываем лямбду
        } else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }
}
