#include <algorithm>

#include "Graph.hpp"
#include "Exceptions.hpp"
#include "DisjointSet.hpp"

namespace narumov {
    void Graph::_swap(Graph &g) noexcept {
        std::swap(_numVerts, g._numVerts);
        std::swap(_adjList, g._adjList);
        std::swap(_deleted, g._deleted);
    }

    Graph::Graph(): _numVerts(0) { }

    Graph::Graph(const Graph &g)
        : _numVerts(g._numVerts), _adjList(g._adjList), _deleted(g._deleted) { }

    Graph::Graph(Graph &&g) noexcept: _numVerts(0) {
        _swap(g);
    }

    Graph &Graph::operator=(const Graph &g) {
        if (this != &g) {
            Graph temp(g);
            _swap(temp);
        }
        return *this;
    }

    Graph &Graph::operator=(Graph &&g) noexcept {
        if (this != &g) {
            _swap(g);
        }
        return *this;
    }

    bool Graph::hasVertices() const {
        return _numVerts > 0;
    }

    bool Graph::hasVertex(Vertex v) const {
        return v >= 0 && v < static_cast<Vertex>(_adjList.size()) && !_deleted[v];
    }

    bool Graph::hasEdge(Vertex u, Vertex v) const {
        if (!hasVertex(u) || !hasVertex(v)) {
            return false;
        }
        for (size_t i = 0; i < _adjList[u].size(); ++i) {
            if (_adjList[u][i].vertex == v) {
                return true;
            }
        }
        return false;
    }

    Vertex Graph::addVertex() {
        if (_adjList.size() == _numVerts) {
            _adjList.push_back(std::vector<VertexWeight>());
            _deleted.push_back(false);
            return static_cast<Vertex>(_numVerts++);
        }
        for (Vertex i = 0; i < static_cast<Vertex>(_adjList.size()); ++i) {
            if (_deleted[i]) {
                _deleted[i] = false;
                _numVerts++;
                return i;
            }
        }
        return 0;
    }

    void Graph::removeVertex(Vertex v) {
        if (!hasVertex(v)) {
            throw VertexDoesNotExist();
        }
        for (Vertex i = 0; i < static_cast<Vertex>(_adjList.size()); ++i) {
            if (i == v) {
                continue;
            }
            for (std::size_t j = 0; j < _adjList[i].size(); ++j) {
                if (_adjList[i][j].vertex == v) {
                    _adjList[i].erase(_adjList[i].begin() + j);
                    break;
                }
            }
        }
        _adjList[v].clear();
        _deleted[v] = true;
        _numVerts--;
    }

    void Graph::addEdge(Vertex u, Vertex v, Weight weight) {
        if (!hasVertex(u) || !hasVertex(v)) {
            throw VertexDoesNotExist();
        }
        if (u == v) {
            throw SelfLoopNotAllowed();
        }
        bool edgeExists = false;
        for (std::size_t j = 0; j < _adjList[u].size(); ++j) {
            if (_adjList[u][j].vertex == v) {
                _adjList[u][j].weight = weight;
                edgeExists = true;
                break;
            }
        }
        if (!edgeExists) {
            _adjList[u].push_back({ v, weight });
            _adjList[v].push_back({ u, weight });
            return;
        }
        for (std::size_t j = 0; j < _adjList[v].size(); ++j) {
            if (_adjList[v][j].vertex == u) {
                _adjList[v][j].weight = weight;
                break;
            }
        }
    }

    Weight Graph::removeEdge(Vertex u, Vertex v) {
        if (!hasVertex(u) || !hasVertex(v)) {
            throw EdgeDoesNotExist();
        }
        Weight weight = 0;
        bool found = false;
        for (std::size_t j = 0; j < _adjList[u].size(); ++j) {
            if (_adjList[u][j].vertex == v) {
                weight = _adjList[u][j].weight;
                _adjList[u].erase(_adjList[u].begin() + j);
                found = true;
                break;
            }
        }
        if (!found) {
            throw EdgeDoesNotExist();
        }
        for (std::size_t j = 0; j < _adjList[v].size(); ++j) {
            if (_adjList[v][j].vertex == u) {
                _adjList[v].erase(_adjList[v].begin() + j);
                break;
            }
        }
        return weight;
    }

    std::vector<Edge> Graph::getEdges() const {
        std::vector<Edge> edges;
        for (Vertex u = 0; u < static_cast<Vertex>(_adjList.size()); ++u) {
            for (std::size_t j = 0; j < _adjList[u].size(); ++j) {
                Vertex v = _adjList[u][j].vertex;
                Weight weight = _adjList[u][j].weight;
                if (u < v) {
                    edges.push_back({ u, v, weight });
                }
            }
        }
        return edges;
    }

    size_t Graph::getNumVertices() const {
        return _numVerts;
    }

    Weight Graph::getWeight() const {
        Weight total = 0;
        for (Vertex u = 0; u < static_cast<Vertex>(_adjList.size()); ++u) {
            for (std::size_t j = 0; j < _adjList[u].size(); ++j) {
                Vertex v = _adjList[u][j].vertex;
                Weight weight = _adjList[u][j].weight;
                if (u < v) {
                    total += weight;
                }
            }
        }
        return total;
    }

    Graph Graph::kruskalMST(const Graph &g) {
        Graph mst;
        for (Vertex i = 0; i < static_cast<Vertex>(g._adjList.size()); ++i) {
            mst.addVertex();
        }
        for (Vertex i = 0; i < static_cast<Vertex>(g._adjList.size()); ++i) {
            if (!g.hasVertex(i)) {
                mst.removeVertex(i);
            }
        }
        DisjointSet ds(g._adjList.size());
        std::vector<Edge> allEdges = g.getEdges();
        std::sort(allEdges.begin(), allEdges.end(),
            [](const Edge &a, const Edge &b) {
                return a.weight < b.weight;
            }
        );
        for(const auto &i : allEdges) {
            Vertex rootU = ds.find(i.u);
            Vertex rootV = ds.find(i.v);
            if (rootU != rootV) {
                mst.addEdge(i.u, i.v, i.weight);
                ds.merge(rootU, rootV);
            }
        }
        return mst;
    }

    void Graph::printGraph(std::ostream &os) const {
        if (getNumVertices() == 0) {
            os << "Graph is empty" << std::endl;
            return;
        }
        os << "Vertexes:" << std::endl;
        bool was = false;
        for (Vertex u = 0; u < static_cast<Vertex>(_adjList.size()); ++u) {
            if (!_deleted[u]) {
                if (was) {
                    os << ", ";
                } else {
                    was = true;
                }
                os << u;
            }
        }
        os << std::endl;
        os << "Edges:" << std::endl;
        for (Vertex u = 0; u < static_cast<Vertex>(_adjList.size()); ++u) {
            if (!_deleted[u]) {
                for (std::size_t j = 0; j < _adjList[u].size(); ++j) {
                    Vertex v = _adjList[u][j].vertex;
                    Weight weight = _adjList[u][j].weight;
                    if (u < v) {
                        os << '(' << u << ", " << v << ") : " << weight << std::endl;
                    }
                }
            }
        }
    }
}
