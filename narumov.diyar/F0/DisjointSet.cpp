#include <numeric>

#include "DisjointSet.hpp"

namespace narumov {
    Vertex DisjointSet::_find(Vertex u) {
        if (_parent[u] != u) {
            _parent[u] = _find(_parent[u]);
        }
        return _parent[u];
    }

    DisjointSet::DisjointSet(std::size_t n): _parent(n), _size(n, 1) {
        std::iota(_parent.begin(), _parent.end(), 0);
    }

    Vertex DisjointSet::find(Vertex u) {
        if (u < 0 || u >= static_cast<Vertex>(_parent.size())) {
            throw VertexDoesNotExist();
        }
        return _find(u);
    }

    void DisjointSet::merge(Vertex u, Vertex v) {
        Vertex rootU = find(u);
        Vertex rootV = find(v);
        if (rootU == rootV) {
            throw SelfLoopNotAllowed();
        }
        if (_size[rootU] < _size[rootV]) {
            std::swap(rootU, rootV);
        }
        _parent[rootV] = rootU;
        _size[rootU] += _size[rootV];
    }
}
