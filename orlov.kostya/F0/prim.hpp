#ifndef __PRIM_HPP__
#define __PRIM_HPP__

#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
#include "graph.hpp"
#include "struct.hpp"

std::vector<Edge> primAlg(const Graph& graph, std::size_t vertex)
{
    std::vector<Edge> res;
    std::vector<bool> visited(graph.getSize(), false);
    visited[vertex] = true;

    auto cmp = [](const Edge& a, const Edge& b) { return a > b; };
    std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> edges(cmp);

    for (const auto& e : graph.getEdges(vertex))
        edges.push(e);

    while (!edges.empty())
    {
        Edge minEdge = edges.top(); edges.pop();

        if (visited[minEdge.first_parent_] != visited[minEdge.second_parent_])
        {
            res.push_back(minEdge);

            std::size_t new_vertex =
                visited[minEdge.first_parent_] ? minEdge.second_parent_ :
                minEdge.first_parent_;
            visited[new_vertex] = true;

            for (const auto& e : graph.getEdges(new_vertex))
                edges.push(e);
        }
    }

    if (static_cast<std::size_t>
            (std::count(visited.begin(), visited.end(), true)) <
            graph.getSize()
        )
        throw std::runtime_error("не связный");

    return res;
}

#endif // !__PRIM_HPP__

