#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>

#include "Menu.hpp"
#include "Exceptions.hpp"

namespace narumov {
    std::vector<MenuItem> menu = {
        { "Add Vertex", std::bind(addVertexAction, std::placeholders::_1) },
        { "Remove Vertex", std::bind(removeVertexAction, std::placeholders::_1) },
        { "Add Edge", std::bind(addEdgeAction, std::placeholders::_1) },
        { "Remove Edge", std::bind(removeEdgeAction, std::placeholders::_1) },
        { "Check if Vertex Exists", std::bind(checkVertexExistsAction, std::placeholders::_1) },
        { "Check if Edge Exists", std::bind(checkEdgeExistsAction, std::placeholders::_1) },
        { "Get Number of Vertices", std::bind(getNumVerticesAction, std::placeholders::_1) },
        { "Get Total Weight of Graph", std::bind(getTotalWeightAction, std::placeholders::_1) },
        { "Print Graph", std::bind(printGraphAction, std::placeholders::_1) },
        { "Compute Minimum Spanning Tree (Kruskal's Algorithm)", std::bind(computeMSTAction, std::placeholders::_1) },
        { "Load Graph from File", std::bind(loadGraphAction, std::placeholders::_1) },
        { "Save Graph to File", std::bind(saveGraphAction, std::placeholders::_1) },
        { "Exit", std::bind(exitAction, std::placeholders::_1) }
    };

    void getIntInput(const std::string &prompt, int &obj) {
        std::cout << prompt;
        std::string line;
        if(!std::getline(std::cin, line)) {
            exit(0);
            return;
        }
        if (line.empty()) {
            throw EmptyInput();
        } else {
            std::istringstream iss(line);
            if (iss >> obj) {
                char remaining;
                if (!(iss >> remaining)) {
                    return;
                }
            }
            throw InvalidInput();
        }
    }

    void getStringInput(const std::string &prompt, std::string &obj) {
        std::cout << prompt;
        if(!std::getline(std::cin, obj)) {
            exit(0);
            return;
        }
        if (obj.empty()) {
            throw EmptyInput();
        } else {
            return;
        }
    }

    Graph loadGraph(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw FileOpenError(filename);
        }
        std::size_t numVertices, numEdges;
        file >> numVertices >> numEdges;
        Graph graph;
        for (std::size_t i = 0; i < numVertices; ++i) {
            graph.addVertex();
        }
        for (std::size_t i = 0; i < numEdges; ++i) {
            Vertex u, v;
            Weight weight;
            file >> u >> v >> weight;
            graph.addEdge(u, v, weight);
        }
        file.close();
        return graph;
    }

    bool saveGraph(const Graph &graph, const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw FileOpenError(filename);
        }
        std::size_t numVertices = graph.getNumVertices();
        std::vector<Edge> edges = graph.getEdges();
        std::size_t numEdges = edges.size();
        file << numVertices << " " << numEdges << std::endl;
        for (std::size_t i = 0; i < numEdges; ++i) {
            Edge edge = edges[i];
            file << edge.u << " " << edge.v << " " << edge.weight << std::endl;
        }
        file.close();
        return true;
    }

    void showMenu(const std::vector<MenuItem>& menu) {
        std::cout << "Graph Operations Menu:" << std::endl;
        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << i + 1 << ". " << menu[i].name << std::endl;
        }
        std::cout << std::endl;
    }

    void runMenu() {
        Graph graph;
        int choice = -1;
        do {
            try {
                showMenu(menu);
                getIntInput("Enter your choice: ", choice);
                std::cout << std::endl;
                if (choice > 0 && choice <= static_cast<int>(menu.size())) {
                    menu[choice - 1].action(graph);
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "\033[31mERROR: " << e.what() << "\033[0m" << std::endl;
            }
            std::cout << std::endl;
            wait();
        } while (choice != static_cast<int>(menu.size()));
    }

    void wait() {
        std::cout << "Press any button to continue...";
        if(getchar() == EOF) {
            exit(0);
        }
        std::cout << std::endl;
    }

    void addVertexAction(Graph& graph) {
        Vertex newVertex = graph.addVertex();
        std::cout << "Vertex " << newVertex << " added" << std::endl;
    }

    void removeVertexAction(Graph& graph) {
        Vertex v;
        getIntInput("Enter vertex to remove: ", v);
        graph.removeVertex(v);
        std::cout << "Vertex " << v << " removed" << std::endl;
    }

    void addEdgeAction(Graph& graph) {
        Vertex u, v;
        Weight weight;
        getIntInput("Enter first vertex (u): ", u);
        getIntInput("Enter second vertex (v): ", v);
        getIntInput("Enter weight: ", weight);
        graph.addEdge(u, v, weight);
        std::cout << "Edge (" << u << ", " << v << ") with weight " << weight << " added" << std::endl;
    }

    void removeEdgeAction(Graph& graph) {
        Vertex u, v;
        getIntInput("Enter first vertex (u): ", u);
        getIntInput("Enter second vertex (v): ", v);
        Weight removedWeight = graph.removeEdge(u, v);
        std::cout << "Edge (" << u << ", " << v << ") with weight " << removedWeight << " removed" << std::endl;
    }

    void checkVertexExistsAction(Graph& graph) {
        Vertex v;
        getIntInput("Enter vertex to check: ", v);
        if (graph.hasVertex(v)) {
            std::cout << "Vertex " << v << " exists" << std::endl;
        } else {
            std::cout << "Vertex " << v << " does not exist" << std::endl;
        }
    }

    void checkEdgeExistsAction(Graph& graph) {
        Vertex u, v;
        getIntInput("Enter first vertex (u): ", u);
        getIntInput("Enter second vertex (v): ", v);
        if (graph.hasEdge(u, v)) {
            std::cout << "Edge (" << u << ", " << v << ") exists" << std::endl;
        } else {
            std::cout << "Edge (" << u << ", " << v << ") does not exist" << std::endl;
        }
    }

    void getNumVerticesAction(Graph& graph) {
        std::cout << "Number of vertices: " << graph.getNumVertices() << std::endl;
    }

    void getTotalWeightAction(Graph& graph) {
        std::cout << "Total weight of graph: " << graph.getWeight() << std::endl;
    }

    void printGraphAction(Graph& graph) {
        graph.printGraph(std::cout);
    }

    void computeMSTAction(Graph& graph) {
        Graph mst = Graph::kruskalMST(graph);
        std::cout << "Minimum Spanning Tree (MST):" << std::endl;
        mst.printGraph(std::cout);
        std::cout << "Total weight of MST: " << mst.getWeight() << std::endl;
    }

    void loadGraphAction(Graph& graph) {
        std::string filename;
        getStringInput("Enter the filename to load the graph from: ", filename);
        graph = loadGraph(filename);
        std::cout << "Graph loaded successfully from " << filename << std::endl;
    }

    void saveGraphAction(Graph& graph) {
        std::string filename;
        getStringInput("Enter the filename to save the graph to: ", filename);
        saveGraph(graph, filename);
        std::cout << "Graph saved successfully to " << filename << std::endl;
    }

    void exitAction(Graph&) {
        std::cout << "Exiting..." << std::endl;
    }
}
