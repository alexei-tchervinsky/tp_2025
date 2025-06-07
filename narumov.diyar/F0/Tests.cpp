#include <iostream>
#include <cassert>
#include <sstream>
#include <random>
#include <chrono>
#include <fstream>

#include "Tests.hpp"
#include "Graph.hpp"
#include "Exceptions.hpp"
#include "Menu.hpp"

namespace narumov {
    void testDefaultConstructor() {
        Graph g;
        assert(!g.hasVertices());
        assert(g.getNumVertices() == 0);
        assert(g.getWeight() == 0);
    }

    void testAddRemoveVertex() {
        Graph g;
        Vertex v0 = g.addVertex();
        Vertex v1 = g.addVertex();
        assert(g.hasVertices());
        assert(g.getNumVertices() == 2);
        g.removeVertex(v0);
        assert(!g.hasVertex(v0));
        assert(g.hasVertex(v1));
        assert(g.getNumVertices() == 1);
        Vertex v2 = g.addVertex();
        assert(v2 == v0);
        assert(g.getNumVertices() == 2);
    }

    void testAddRemoveEdge() {
        Graph g;
        Vertex u = g.addVertex();
        Vertex v = g.addVertex();
        g.addEdge(u, v, 5);
        assert(g.hasEdge(u, v) && g.hasEdge(v, u));
        assert(g.getWeight() == 5);
        g.addEdge(u, v, 10);
        assert(g.getWeight() == 10);
        Weight w = g.removeEdge(u, v);
        assert(w == 10);
        assert(!g.hasEdge(u, v));
        assert(g.getWeight() == 0);
    }

    void testExceptions() {
        Graph g;
        bool caught = false;
        try {
            g.removeVertex(1);
        } catch (const VertexDoesNotExist &) {
            caught = true;
        }
        assert(caught);
        caught = false;
        Vertex v0 = g.addVertex();
        try {
            g.removeVertex(v0 + 1);
        } catch (const VertexDoesNotExist &) {
            caught = true;
        }
        assert(caught);
        caught = false;
        try {
            g.addEdge(v0, v0 + 1, 1);
        } catch (const VertexDoesNotExist &) {
            caught = true;
        }
        assert(caught);
        caught = false;
        try {
            g.addEdge(v0, v0, 1);
        } catch (const SelfLoopNotAllowed &) {
            caught = true;
        }
        assert(caught);
        caught = false;
        try {
            g.removeEdge(v0, v0);
        } catch (const EdgeDoesNotExist &) {
            caught = true;
        }
        assert(caught);
        caught = false;
        Vertex v1 = g.addVertex();
        try {
            g.removeEdge(v0, v1);
        } catch (const EdgeDoesNotExist &) {
            caught = true;
        }
        assert(caught);
    }

    void testCopyMoveAssign() {
        Graph g;
        Vertex u = g.addVertex();
        Vertex v = g.addVertex();
        g.addEdge(u, v, 7);
        Graph gCopy(g);
        assert(gCopy.hasEdge(u, v) && gCopy.getWeight() == 7);
        Graph gMovedCtor(std::move(gCopy));
        assert(gMovedCtor.hasEdge(u, v) && gMovedCtor.getWeight() == 7);
        Graph gAssign;
        gAssign = gMovedCtor;
        assert(gAssign.hasEdge(u, v) && gAssign.getWeight() == 7);
        Graph gMoveAssign;
        gMoveAssign = std::move(gAssign);
        assert(gMoveAssign.hasEdge(u, v) && gMoveAssign.getWeight() == 7);
    }

    void testGetEdgesAndWeight() {
        Graph g;
        for (std::size_t i = 0; i < 4; ++i) {
            g.addVertex();
        }
        g.addEdge(0, 1, 3);
        g.addEdge(1, 2, 4);
        g.addEdge(2, 3, 5);
        g.addEdge(3, 0, 6);
        auto edges = g.getEdges();
        std::size_t count = 0;
        int totalW = 0;
        while (edges.size()) {
            auto e = edges.back();
            edges.pop_back();
            totalW += e.weight;
            ++count;
        }
        assert(count == 4);
        assert(totalW == g.getWeight());
    }

    void testKruskalMST() {
        Graph g;
        for (std::size_t i = 0; i < 5; ++i) {
            g.addVertex();
        }
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(2, 3, 3);
        g.addEdge(3, 4, 4);
        g.addEdge(4, 0, 5);
        g.addEdge(0, 2, 6);
        Graph mst = Graph::kruskalMST(g);
        assert(mst.getNumVertices() == 5);
        assert(mst.getWeight() == 10);
        auto edges = mst.getEdges();
        std::size_t cnt = 0;
        while (edges.size()) {
            edges.back();
            edges.pop_back();
            ++cnt;
        }
        assert(cnt == 4);
    }

    void testPrintGraph() {
        Graph g;
        std::ostringstream os;
        g.printGraph(os);
        assert(os.str() == "Graph is empty\n");
        g.addVertex();
        g.addVertex();
        g.addEdge(0, 1, 9);
        os.str("");
        os.clear();
        g.printGraph(os);
        std::string out = os.str();
        assert(out.find("(0, 1) : 9") != std::string::npos);
    }

    void testCompleteGraph(std::size_t n, Weight w) {
        Graph g;
        for (std::size_t u = 0; u < n; ++u) {
            g.addVertex();
        }
        for (std::size_t u = 0; u < n; ++u) {
            for (std::size_t v = u + 1; v < n; ++v) {
                g.addEdge(u, v, w);
            }
        }
        auto edges = g.getEdges();
        std::size_t cnt = 0;
        while (edges.size()) {
            edges.pop_back();
            ++cnt;
        }
        assert(cnt == n * (n - 1) / 2);
        assert(g.getWeight() == static_cast<Weight>(w * (n * (n - 1) / 2)));
    }

    void testDisconnectedGraph(std::size_t n) {
        Graph g;
        for (std::size_t i = 0; i < n; ++i) {
            g.addVertex();
        }
        Graph mst = Graph::kruskalMST(g);
        assert(mst.getWeight() == 0);
        assert(mst.getNumVertices() == n);
    }

    void testLargeRandomGraph(std::size_t n, std::size_t m) {
        Graph g;
        for (std::size_t i = 0; i < n; ++i) {
            g.addVertex();
        }
        std::mt19937_64 rng(12345);
        std::uniform_int_distribution<std::size_t> distV(0, n - 1);
        std::uniform_int_distribution<Weight> distW(1, 100);
        for (std::size_t i = 0; i < m; ++i) {
            auto u = distV(rng);
            auto v = distV(rng);
            if (u != v) {
                g.addEdge(u, v, distW(rng));
            }
        }
        for (std::size_t i = 0; i < n / 10; ++i) {
            auto v = distV(rng); if (g.hasVertex(v)) {
                g.removeVertex(v);
            }
        }
        auto edges = g.getEdges();
        while (edges.size()) {
            auto e = edges.back();
            edges.pop_back();
            assert(g.hasEdge(e.u, e.v));
        }
    }

    void testStressRandomOperations(std::size_t n) {
        Graph g;
        std::mt19937 rng(67890);
        std::uniform_int_distribution<int> op(0, 3);
        std::uniform_int_distribution<std::size_t> distV(0, n - 1);
        std::uniform_int_distribution<Weight> distW(1, 100);
        for (std::size_t i = 0; i < 100000; ++i) {
            int action = op(rng);
            auto u = distV(rng);
            auto v = distV(rng);
            switch (action) {
                case 0:
                {
                    g.addVertex(); break;
                }
                case 1:
                {
                    if (g.hasVertex(u)) {
                        g.removeVertex(u);
                    } break;
                }
                case 2:
                {
                    if (g.hasVertex(u) && g.hasVertex(v) && u != v) {
                        g.addEdge(u, v, distW(rng));
                    } break;
                }
                case 3:
                {
                    if (g.hasVertex(u) && g.hasVertex(v) && g.hasEdge(u, v)) {
                        g.removeEdge(u, v);
                    } break;
                }
            }
        }
    }

    void testStressKruskal(std::size_t n, std::size_t m) {
        Graph g;
        for (std::size_t i = 0; i < n; ++i) {
            g.addVertex();
        }
        std::mt19937_64 rng(54321);
        std::uniform_int_distribution<std::size_t> distV(0, n - 1);
        std::uniform_int_distribution<Weight> distW(1, 100);
        for (std::size_t i = 0; i < m; ++i) {
            auto u = static_cast<Vertex>(distV(rng));
            auto v = static_cast<Vertex>(distV(rng));
            if (u != v) {
                g.addEdge(u, v, distW(rng));
            }
        }
        auto start = std::chrono::high_resolution_clock::now();
        Graph mst = Graph::kruskalMST(g);
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Kruskal stress test on graph n = " << n << ", m = " << m << " completed in " << dur << " ms" << std::endl;
        assert(mst.getNumVertices() == g.getNumVertices());
    }

    void testCustom(const std::string &filename) {
        std::cout << "Verifying " << filename << std::endl;
        std::ifstream in(filename);
        assert(in.is_open());
        std::size_t n, m;
        assert(in >> n >> m);
        Graph g;
        for (std::size_t i = 0; i < n; ++i) {
            g.addVertex();
        }
        for (std::size_t i = 0; i < m; ++i) {
            Vertex u, v;
            Weight w;
            assert(in >> u >> v >> w);
            g.addEdge(u, v, w);
        }
        Weight declaredWeight;
        assert(in >> declaredWeight);
        Graph mst = Graph::kruskalMST(g);
        Weight actualWeight = mst.getWeight();
        assert(actualWeight == declaredWeight);
    }

    void testFull() {
        testDefaultConstructor();
        testAddRemoveVertex();
        testAddRemoveEdge();
        testExceptions();
        testCopyMoveAssign();
        testGetEdgesAndWeight();
        testKruskalMST();
        testPrintGraph();
        testCompleteGraph(100, 3);
        testDisconnectedGraph(1000);
        testLargeRandomGraph(1000, 1000);
        testStressRandomOperations(1000);
        testStressKruskal(100000, 500000);
        testCustom("test1.txt");
        testCustom("test2.txt");
        testCustom("test3.txt");
        std::cout << "All tests passed successfully" << std::endl << std::endl;
        wait();
    }
}
