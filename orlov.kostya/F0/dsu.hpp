#ifndef __DSU_HPP__
#define __DSU_HPP__

#include <vector>
#include <stdexcept>

class DSU {
private:
    std::vector<std::size_t> parent_;
    std::vector<std::size_t> rank_;

public:
    DSU(std::size_t size) : parent_(size), rank_(size, 0)
    {
        for (std::size_t i = 0; i < size; ++i)
            parent_[i] = i;
    }

    std::size_t find(std::size_t u)
    {
        if (u >= parent_.size())
            throw std::out_of_range("Vertex index out of range");
        if (parent_[u] != u)
            parent_[u] = find(parent_[u]);
        return parent_[u];
    }

    void merge(std::size_t u, std::size_t v)
    {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (rank_[u] < rank_[v])
            parent_[u] = v;
        else if (rank_[u] > rank_[v])
            parent_[v] = u;
        else
        {
            parent_[v] = u;
            ++rank_[u];
        }
    }
};

#endif // !__DSU_HPP__

