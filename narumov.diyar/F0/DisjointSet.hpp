#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

#include "Types.hpp"
#include "Exceptions.hpp"

namespace narumov {
    class DisjointSet {
    private:
        std::vector<Vertex> _parent;
        std::vector<std::size_t> _size;

        Vertex _find(Vertex);

    public:
        explicit DisjointSet(std::size_t);

        Vertex find(Vertex);
        void merge(Vertex, Vertex);
    };
}

#endif
