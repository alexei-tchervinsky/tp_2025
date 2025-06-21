#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <vector>
#include <iostream>
#include <stdexcept>
#include "struct.hpp"

class Graph
{
public:
    Graph(std::size_t size = 10);

    void addVertex(std::size_t index);
    void addEdge(std::size_t value, std::size_t i, std::size_t j);

    void removeVertex(std::size_t index);
    void removeEdge(std::size_t i, std::size_t j);
    bool hasVertex(std::size_t index) const;
    bool hasEdge(std::size_t i, std::size_t j) const;

    std::size_t getWeight(std::size_t i, std::size_t j) const;
    std::vector<Edge> getAllEdges() const;
    std::vector<Edge> getEdges(std::size_t vertex) const;
    std::size_t getSize() const;

    void displayEdges();
    void displayAll();

private:
    std::size_t size_;
    std::vector<std::vector<std::size_t>> matrix_;
    std::vector<bool> usedVertex_;
    std::vector<bool> deletedVertex_;
};

Graph::Graph(std::size_t size) :
    size_(size),
    matrix_(size, std::vector<std::size_t>(size, 0)),
    usedVertex_(size, false),
    deletedVertex_(size, false)
{}

void Graph::addVertex(std::size_t index)
{
    if (index >= size_)
    {
        size_ = index + 1;
        matrix_.resize(size_, std::vector<std::size_t>(size_, 0));

        for (auto& row : matrix_) row.resize(size_, 0);

        usedVertex_.resize(size_, false);
        deletedVertex_.resize(size_, false);
    }

    if (usedVertex_[index])
        throw std::runtime_error("Vertex already used");

    usedVertex_[index] = true;
    deletedVertex_[index] = false;
}

void Graph::addEdge(std::size_t value, std::size_t i, std::size_t j)
{
    if (i >= size_ || j >= size_)
        throw std::runtime_error("Invalid index");
    if (!usedVertex_[i] || !usedVertex_[j])
        throw std::runtime_error("Vertex not used");

    matrix_[i][j] = value;
    matrix_[j][i] = value;
}

void Graph::removeVertex(std::size_t index)
{
    if (index >= size_ || deletedVertex_[index] || !usedVertex_[index])
        throw std::runtime_error("Invalid index");

    for (std::size_t i = 0; i < size_; ++i)
    {
        matrix_[i][index] = 0;
        matrix_[index][i] = 0;
    }

    usedVertex_[index] = false;
    deletedVertex_[index] = true;
}

void Graph::removeEdge(std::size_t i, std::size_t j)
{
    if (i >= size_ || j >= size_ || !usedVertex_[i] || !usedVertex_[j])
        throw std::runtime_error("Invalid edge");

    matrix_[i][j] = 0;
    matrix_[j][i] = 0;
}

bool Graph::hasVertex(std::size_t index) const
{
    return index < size_ && usedVertex_[index] && !deletedVertex_[index];
}

bool Graph::hasEdge(std::size_t i, std::size_t j) const
{
    return i < size_ && j < size_ && matrix_[i][j] != 0;
}

std::size_t Graph::getWeight(std::size_t i, std::size_t j) const
{
    return (i < size_ && j < size_) ? matrix_[i][j] : 0;
}

std::vector<Edge> Graph::getAllEdges() const
{
    std::vector<Edge> res;
    for (std::size_t i = 0; i < size_; ++i)
    {
        if (!usedVertex_[i] || deletedVertex_[i]) continue;

        for (std::size_t j = i + 1; j < size_; ++j)
        {
            if (matrix_[i][j] != 0)
                res.emplace_back(matrix_[i][j], i, j);
        }
    }
    return res;
}

std::vector<Edge> Graph::getEdges(std::size_t vertex) const
{
    std::vector<Edge> res;
    if (vertex >= size_ || deletedVertex_[vertex] || !usedVertex_[vertex])
        return res;

    for (std::size_t i = 0; i < size_; ++i)
    {
        if (matrix_[vertex][i] != 0)
            res.emplace_back(matrix_[vertex][i], vertex, i);
    }

    return res;
}

std::size_t Graph::getSize() const
{
    return size_;
}

void Graph::displayEdges() {
    std::cout << "Active vertices: ";

    for (std::size_t i = 0; i < size_; ++i)
    {
        if (usedVertex_[i] && !deletedVertex_[i])
            std::cout << i << ' ';
    }

    std::cout << "\nEdges (vertix1->vertix2:value):\n";

    for (std::size_t i = 0; i < size_; ++i)
    {
        if (!usedVertex_[i] || deletedVertex_[i]) continue;

        for (std::size_t j = 0; j < size_; ++j)
        {
            if (!usedVertex_[j] || deletedVertex_[j] || i == j) continue;
            std::cout << i << "->" << j << ":" << matrix_[i][j] << "\n";
        }

        std::cout << "\n";
    }
}

void Graph::displayAll()
{
    std::cout << "Adjacency matrix:" << std::endl;

    std::cout << "   ";
    for (std::size_t i = 0; i < size_; ++i)
        std::cout << i << ' ';

    std::cout << std::endl;

    std::size_t totalWeight = 0;
    std::size_t edgeCount = 0;

    for (std::size_t i = 0; i < size_; ++i)
    {
        std::cout << i << ": ";

        for (std::size_t j = 0; j < size_; ++j)
        {
            std::cout << matrix_[i][j] << ' ';

            if (i < j && matrix_[i][j] != 0)
            {
                totalWeight += matrix_[i][j];
                edgeCount++;
            }
        }

        if (!usedVertex_[i]) std::cout << "(not used Vertex)";
        else if (deletedVertex_[i]) std::cout << "(deleted Vertex)";

        std::cout << std::endl;
    }

    std::cout << "\nGraph statistics:" << std::endl;
    std::cout << "- Active vertices: ";
    for (std::size_t i = 0; i < size_; ++i)
    {
        if (usedVertex_[i] && !deletedVertex_[i])
            std::cout << i << ' ';
    }
    std::cout << std::endl;
    std::cout << "- Total edges: " << edgeCount << std::endl;
    std::cout << "- Total weight: " << totalWeight << std::endl;
    std::cout
        << "- Average edge weight: "
        << (edgeCount ? (double)totalWeight/edgeCount : 0) << std::endl;

    std::cout << "End of adjacency matrix" << std::endl;
}

#endif // !__GRAPH_HPP__

