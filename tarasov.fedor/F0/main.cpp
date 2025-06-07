#include "graph_TP.hpp"
#include <iostream>
#include <numeric>

void runKruskalTest1_Empty() {
    std::cout << "  --- Kruskal Test 1: Empty Graph ---" << std::endl;
    Graph g;
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (empty graph):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should be empty." << std::endl << std::endl;
}

void runKruskalTest2_SingleNode() {
    std::cout << "  --- Kruskal Test 2: Single Node Graph (no edges) ---" << std::endl;
    Graph g;
    g.addNode(1);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (single node):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: "
                 "MST should contain node 1 with no edges." << std::endl << std::endl;
}

void runKruskalTest3_SimpleConnected() {
    std::cout << "  --- Kruskal Test 3: "
                 "Simple Connected Graph (3 nodes) ---" << std::endl;
    Graph g;
    g.addNode(0);
    g.addNode(1);
    g.addNode(2);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 3);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (simple connected graph):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: "
                 "MST should contain edges (0,1,1) and (1,2,2)." << std::endl << std::endl;
}

void runKruskalTest4_Disconnected() {
    std::cout << "  --- Kruskal Test 4: Disconnected Graph (2 components) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1); g.addEdge(2, 3, 2);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (disconnected graph, forest):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST (forest) should "
                 "contain edges (0,1,1) and (2,3,2)." << std::endl << std::endl;
}

void runKruskalTest5_MultiplePaths() {
    std::cout << "  --- Kruskal Test 5: Graph with Multiple Paths ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1);
    g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 3, 1);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (graph with multiple paths):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should contain edges"
                 " (0,1,1), (2,3,1), (0,2,2). Total weight = 4." << std::endl << std::endl;
}

void runPrimTest1_Empty() {
    std::cout << "  --- Prim Test 1: Empty Graph ---" << std::endl;
    Graph g;
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (empty graph):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should be empty." << std::endl << std::endl;
}

void runPrimTest2_SingleNode() {
    std::cout << "  --- Prim Test 2: Single Node Graph (no edges) ---" << std::endl;
    Graph g;
    g.addNode(1);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (single node):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should "
                 "contain node 1 with no edges." << std::endl << std::endl;
}

void runPrimTest3_SimpleConnected() {
    std::cout << "  --- Prim Test 3: Simple Connected Graph (3 nodes) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 3);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (simple connected graph):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should contain edges (0,1,1)"
                 " and (1,2,2). Total weight = 3." << std::endl << std::endl;
}

void runPrimTest4_Disconnected() {
    std::cout << "  --- Prim Test 4: Disconnected Graph (2 components) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (disconnected graph, Prim):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should contain edge (0,1,1). "
                 "Nodes 2,3 will be in MST but without connecting edges." << std::endl << std::endl;
}

void runPrimTest5_MultiplePaths() {
    std::cout << "  --- Prim Test 5: Graph with Multiple Paths ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1); g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3); g.addEdge(2, 3, 1);
    std::cout << "  Original graph:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (graph with multiple paths, Prim):" << std::endl;
    mst.printGraph();
    std::cout << "  Expected result: MST should contain edges (0,1,1), "
                 "(2,3,1), (0,2,2). Total weight = 4." << std::endl << std::endl;
}

void runGraphMethodsTests() {
    std::cout << "  --- Graph Class Methods Tests ---" << std::endl;
    Graph myGraph;

    std::cout << "\n  1. Initial state (empty graph):" << std::endl;
    myGraph.printGraph();
    std::cout << "  Is graph empty? "
    << (myGraph.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << "\n  2. Adding nodes:" << std::endl;
    myGraph.addNode(10); myGraph.addNode(20); myGraph.addNode(5);
    myGraph.addNode(20);
    myGraph.printGraph();
    std::cout << "  Is graph empty? "
    << (myGraph.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "  Does node 10 exist? "
    << (myGraph.hasNode(10) ? "Yes" : "No") << std::endl;
    std::cout << "  Does node 15 exist? "
    << (myGraph.hasNode(15) ? "Yes" : "No") << std::endl;

    std::cout << "\n  3. Adding edges:" << std::endl;
    myGraph.addEdge(10, 20, 15);
    myGraph.addEdge(5, 10, 7);
    myGraph.addEdge(5, 20, 10);
    myGraph.addEdge(1, 2, 5);
    myGraph.addEdge(10, 20, 15);
    myGraph.printGraph();
    std::cout << "  Does edge (10, 20) exist? "
    << (myGraph.hasEdge(10, 20) ? "Yes" : "No") << std::endl;
    std::cout << "  Does edge (20, 10) exist? "
    << (myGraph.hasEdge(20, 10) ? "Yes" : "No") << " (checking undirectedness)" << std::endl;
    std::cout << "  Does edge (10, 50) exist? "
    << (myGraph.hasEdge(10, 50) ? "Yes" : "No") << std::endl;

    std::cout << "\n  4. Removing node:" << std::endl;
    std::cout << "  Removing node 10:" << std::endl;
    myGraph.removeNode(10);
    myGraph.printGraph();
    std::cout << "  Does node 10 exist? "
    << (myGraph.hasNode(10) ? "Yes" : "No") << std::endl;
    std::cout << "  Does edge (5, 10) exist? "
    << (myGraph.hasEdge(5, 10) ? "Yes" : "No") << std::endl;
    std::cout << "  Does edge (5, 20) exist? "
    << (myGraph.hasEdge(5, 20) ? "Yes" : "No") << " (this edge should remain)" << std::endl;

    std::cout << "  Attempt to remove non-existent node 100:" << std::endl;
    myGraph.removeNode(100);
    myGraph.printGraph();
    std::cout << std::endl;
}

void runTests(const std::string& testType) {
    std::cout << "==============================================" << std::endl;
    std::cout << "RUNNING TESTS FOR: \"" << testType << "\"" << std::endl;
    std::cout << "==============================================" << std::endl;

    if (testType == "Graph") {
        runGraphMethodsTests();
    } else if (testType == "Kruskal") {
        runKruskalTest1_Empty();
        runKruskalTest2_SingleNode();
        runKruskalTest3_SimpleConnected();
        runKruskalTest4_Disconnected();
        runKruskalTest5_MultiplePaths();
    } else if (testType == "Prim") {
        runPrimTest1_Empty();
        runPrimTest2_SingleNode();
        runPrimTest3_SimpleConnected();
        runPrimTest4_Disconnected();
        runPrimTest5_MultiplePaths();
    } else {
        std::cout << "Unknown test type: \"" << testType << "\"" << std::endl;
        std::cout << "Valid values: \"Graph\","
                     " \"Prim\", \"Kruskal\"" << std::endl;
    }
    std::cout << "--- Testing for \"" << testType << "\" completed ---" << std::endl << std::endl;
}

int main() {
    std::string c;

    std::cout << "Enter command ('Graph', 'Prim', 'Kruskal')." << std::endl;

    while (std::cin >> c) {
        if (c != "Graph" && c != "Prim" && c != "Kruskal") {
            std::cout << "Invalid command: " << c
            << ". Please enter 'Graph', 'Prim' or 'Kruskal'." << std::endl;
        } else {
            runTests(c);
        }
        std::cout << "Enter next command:" << std::endl;
    }

    if (std::cin.eof()) {
        std::cout << "Input completed (reached end of file)." << std::endl;
    } else if (std::cin.fail()) {
        std::cerr << "Input error. Possibly entered incorrect data type." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
