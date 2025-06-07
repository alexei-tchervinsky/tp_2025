#ifndef TYPES_H
#define TYPES_H

#include <utility>

namespace narumov {
    typedef int Vertex;
    typedef int Weight;

    struct VertexWeight {
        Vertex vertex;
        Weight weight;
    };

    struct Edge {
        Vertex u, v;
        Weight weight;
    };
}

#endif
