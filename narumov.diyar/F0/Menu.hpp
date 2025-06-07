#ifndef MENU_HPP
#define MENU_HPP

#include <string>
#include <vector>
#include <functional>

#include "Graph.hpp"

namespace narumov {
    struct MenuItem {
        std::string name;
        std::function<void(Graph&)> action;
    };

    extern std::vector<MenuItem> menu;

    void getIntInput(const std::string &, int&);
    void getStringInput(const std::string &, std::string&);
    Graph loadGraph(const std::string &);
    bool saveGraph(const Graph &, const std::string &);
    void showMenu(const std::vector<MenuItem>&);
    void runMenu();
    void wait();

    void addVertexAction(Graph& graph);
    void removeVertexAction(Graph& graph);
    void addEdgeAction(Graph& graph);
    void removeEdgeAction(Graph& graph);
    void checkVertexExistsAction(Graph& graph);
    void checkEdgeExistsAction(Graph& graph);
    void getNumVerticesAction(Graph& graph);
    void getTotalWeightAction(Graph& graph);
    void printGraphAction(Graph& graph);
    void computeMSTAction(Graph& graph);
    void loadGraphAction(Graph& graph);
    void saveGraphAction(Graph& graph);
    void exitAction(Graph& graph);
}

#endif
