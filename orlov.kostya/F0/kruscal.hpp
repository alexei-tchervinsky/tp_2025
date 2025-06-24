#ifndef __KRUSCAL_HPP__
#define __KRUSCAL_HPP__

#include <vector>
#include <algorithm>
#include "graph.hpp"
#include "dsu.hpp"
#include "struct.hpp"

std::vector<Edge> kruscalAlg(const Graph& src)
{
    std::vector<Edge> edges = src.getAllEdges();
    std::sort(edges.begin(), edges.end());

    DSU tmp(src.getSize());
    std::vector<Edge> res;

    for (const Edge& element : edges)
    {
        if (tmp.find(element.first_parent_) != tmp.find(element.second_parent_))
        {
            res.push_back(element);
            tmp.merge(element.first_parent_, element.second_parent_);
        }
    }

    if (res.size() < src.getSize() - 1)
        throw std::runtime_error("не связный");

    return res;
}

#endif // !__KRUSCAL_HPP__

