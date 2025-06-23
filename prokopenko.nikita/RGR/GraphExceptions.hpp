#pragma once

#include <exception>
#include <string>
#include <utility>

class GraphException : public std::exception {
protected:
    std::string message;

public:
    explicit GraphException(std::string str)
        : message(std::move(str)) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class VertexAlreadyExist : public GraphException {
public:
    explicit VertexAlreadyExist(const std::string& name)
        : GraphException("Vertex already exists: " + name) {}
};

class VertexDontExist : public GraphException {
public:
    explicit VertexDontExist(const std::string& name)
        : GraphException("Vertex doesn't exist: " + name) {}
};

class CantAddEdge : public GraphException {
public:
    CantAddEdge(const std::string& from, const std::string& to)
        : GraphException("Can't add edge: " + from + " -> " + to) {}
};

class EdgeAlreadyExist : public GraphException {
public:
    EdgeAlreadyExist(const std::string& from, const std::string& to)
        : GraphException("Edge already exists: " + from + " -> " + to) {}
};

class GraphHasCycle : public GraphException {
public:
    GraphHasCycle()
        : GraphException("Graph has a cycle. Topological sort is not possible.") {}
};
