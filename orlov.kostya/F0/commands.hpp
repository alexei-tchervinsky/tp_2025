#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

#include "graph.hpp"
#include "kruscal.hpp"
#include "prim.hpp"
#include "struct.hpp"

extern std::map<std::string, std::function<void()>> commandsList;
void executeCommand(const std::string& command);
void testGraph();
void testKruscal();
void testPrim();
void testKruscalAndPrimIndMst();
void testKruscalAndPrimDiffMst();

std::map<std::string, std::function<void()>> commandsList =
{
    { "GRAPH", std::bind(testGraph) },
    { "KRUSCAL", std::bind(testKruscal) },
    { "PRIM", std::bind(testPrim) },
    { "KRUSCAL AND PRIM IND MST", std::bind(testKruscalAndPrimIndMst) },
    { "KRUSCAL AND PRIM DIFF MST", std::bind(testKruscalAndPrimDiffMst) }
};

void executeCommand(const std::string& command)
{
    auto it = commandsList.find(command);

    if (it == commandsList.end())
    {
        std::cout << "\n\tThis command not found in list\n";
        return;
    }

    it->second();
}

void testGraph()
{
    Graph test(10);

    std::cout << "Tests for ATD Graph (graph on adjacency matrix)" << std::endl;

    std::cout << "- Add Vertex: 0, 1, 5, 3, 9" << std::endl << std::endl;

    test.addVertex(0);
    test.addVertex(1);
    test.addVertex(5);
    test.addVertex(3);
    test.addVertex(9);
    test.displayAll();

    std::cout << "\n- Add Edge:" << std::endl;
    std::cout
            << "-- Edge 0->9 value: 1" << std::endl
            << "-- Edge 5->3 value: 1" << std::endl
            << "-- Edge 5->9 value: 1" << std::endl
            << std::endl
            ;

    test.addEdge(1, 0, 9);
    test.addEdge(1, 5, 3);
    test.addEdge(1, 5, 9);
    test.displayEdges();

    std::cout << "- Remove Vertex 1" << std::endl;
    std::cout << "Remove Edge 9->0" << std::endl << std::endl;

    test.removeVertex(1);
    test.removeEdge(9, 0);

    test.displayEdges();
    test.displayAll();
}

void testKruscal()
{
    std::cout << "\nTest for kruscal alg\n";

    Graph testGraph(5);

    testGraph.addVertex(0);
    testGraph.addVertex(1);
    testGraph.addVertex(2);
    testGraph.addVertex(3);
    testGraph.addVertex(4);
    testGraph.addVertex(5);

    testGraph.addEdge(4, 0, 1);
    testGraph.addEdge(6, 0, 5);
    testGraph.addEdge(6, 1, 2);
    testGraph.addEdge(8, 2, 3);
    testGraph.addEdge(5, 2, 5);
    testGraph.addEdge(3, 3, 4);
    testGraph.addEdge(5, 3, 5);
    testGraph.addEdge(2, 4, 5);
    testGraph.displayAll();

    std::cout << "\nResult of Kruskal algorithm:" << std::endl;

    std::vector<Edge> kruscal = kruscalAlg(testGraph);

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        std::cout << kruscal[i] << std::endl;

    std::size_t totalKruscal = 0;

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        totalKruscal += kruscal[i].value_;

    std::cout << "total for Kruscal alg: " << totalKruscal << std::endl << std::endl;
}

void testPrim()
{
    std::cout << "\nTest for prim alg\n";

    Graph testGraph(5);

    testGraph.addVertex(0);
    testGraph.addVertex(1);
    testGraph.addVertex(2);
    testGraph.addVertex(3);
    testGraph.addVertex(4);

    testGraph.addEdge(2, 0, 1);
    testGraph.addEdge(6, 0, 3);
    testGraph.addEdge(3, 1, 2);
    testGraph.addEdge(8, 1, 3);
    testGraph.addEdge(5, 1, 4);
    testGraph.addEdge(7, 2, 4);
    testGraph.addEdge(9, 3, 4);
    testGraph.displayAll();

    std::cout << "Result of Prim algorithm (start Vertex 0):" << std::endl;

    std::vector<Edge> prim = primAlg(testGraph, 0);

    for (std::size_t i = 0; i < prim.size(); ++i)
        std::cout << prim[i] << std::endl;

    std::size_t totalPrim = 0;

    for (std::size_t i = 0; i < prim.size(); ++i)
        totalPrim += prim[i].value_;

    std::cout << "total for Prim alg: " << totalPrim << std::endl;
}

void testKruscalAndPrimIndMst()
{
    std::cout << "\nTest for Kruskal and Prim algorithm" << std::endl;
    std::cout << "Create graph with identical MST for Kruskal and Prim:\n" << std::endl;

    Graph graph1(5);

    graph1.addVertex(0);
    graph1.addVertex(1);
    graph1.addVertex(2);
    graph1.addVertex(3);
    graph1.addVertex(4);

    graph1.addEdge(6, 0, 1);
    graph1.addEdge(1, 0, 2);
    graph1.addEdge(5, 0, 3);
    graph1.addEdge(3, 1, 2);
    graph1.addEdge(2, 1, 4);
    graph1.addEdge(4, 2, 4);
    graph1.addEdge(7, 4, 3);

    graph1.displayEdges();
    graph1.displayAll();

    std::cout << "\nResult of Kruskal algorithm:" << std::endl;

    std::vector<Edge> kruscal = kruscalAlg(graph1);

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        std::cout << kruscal[i] << std::endl;

    std::size_t totalKruscal = 0;

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        totalKruscal += kruscal[i].value_;

    std::cout << "total for Kruscal alg: " << totalKruscal << std::endl << std::endl;

    std::cout << "Result of Prim algorithm (start Vertex 0):" << std::endl;

    std::vector<Edge> prim = primAlg(graph1, 0);

    for (std::size_t i = 0; i < prim.size(); ++i)
        std::cout << prim[i] << std::endl;

    std::size_t totalPrim = 0;

    for (std::size_t i = 0; i < prim.size(); ++i)
        totalPrim += prim[i].value_;

    std::cout << "total for Prim alg: " << totalPrim << std::endl;
}

void testKruscalAndPrimDiffMst()
{
    std::cout << "\nCreate graph with diffrent MST for Kruskal and Prim:\n" << std::endl;
    Graph graph2(4);

    graph2.addVertex(0);
    graph2.addVertex(1);
    graph2.addVertex(2);
    graph2.addVertex(3);

    graph2.addEdge(2, 0, 1);
    graph2.addEdge(2, 0, 2);
    graph2.addEdge(1, 1, 2);
    graph2.addEdge(1, 1, 3);
    graph2.addEdge(1, 2, 3);

    graph2.displayEdges();
    graph2.displayAll();

    std::vector<Edge> kruscal = kruscalAlg(graph2);
    std::vector<Edge> prim = primAlg(graph2, 2);

    std::cout << "\nResult of Kruskal algorithm:" << std::endl;

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        std::cout << kruscal[i] << std::endl;

    std::size_t totalKruscal = 0;

    for (std::size_t i = 0; i < kruscal.size(); ++i)
        totalKruscal += kruscal[i].value_;

    std::cout << "total for Kruscal alg: " << totalKruscal << std::endl;

    std::cout << "\nResult of Prim algorithm (start Vertex 2):" << std::endl;

    for (std::size_t i = 0; i < prim.size(); ++i)
        std::cout << prim[i] << std::endl;

    std::size_t totalPrim = 0;

    for (std::size_t i = 0; i < prim.size(); ++i)
        totalPrim += prim[i].value_;

    std::cout << "total for Prim alg: " << totalPrim << std::endl;
}

#endif

