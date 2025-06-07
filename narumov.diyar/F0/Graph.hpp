#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Types.hpp"

namespace narumov {
    class Graph {
    private:
        std::size_t _numVerts;
        std::vector<std::vector<VertexWeight>> _adjList;
        std::vector<bool> _deleted;

        void _swap(Graph &) noexcept;

    public:
        Graph();
        Graph(const Graph &);
        Graph(Graph &&) noexcept;

        Graph &operator=(const Graph &);
        Graph &operator=(Graph &&) noexcept;

        bool hasVertices() const;
        bool hasVertex(Vertex) const;
        bool hasEdge(Vertex, Vertex) const;

        Vertex addVertex();
        void removeVertex(Vertex);

        void addEdge(Vertex, Vertex, Weight);
        Weight removeEdge(Vertex, Vertex);

        std::vector<Edge> getEdges() const;
        std::size_t getNumVertices() const;
        Weight getWeight() const;

        static Graph kruskalMST(const Graph &);

        void printGraph(std::ostream &) const;
    };
}

#endif
