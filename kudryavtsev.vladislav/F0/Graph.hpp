#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <limits>

class Graph {
public:
    using Node = int;
    using Weight = double;
    struct Edge {
        Node to;
        Weight weight;
    };
    Graph();
    bool empty() const;
    bool has_node(Node node) const;
    bool has_edge(Node from, Node to);
    void add_node(Node node);
    void remove_node(Node node);
    void add_edge(Node from, Node to, Weight weight);
    Weight remove_edge(Node from, Node to);
    std::vector<Node> nodes() const;
    const std::vector<Edge>& edges_from(Node node);
    bool bellman_ford(Node source, std::unordered_map<Node, Weight>& dist, std::unordered_map<Node, Node>& prev);

private:
    std::unordered_map<Node, std::vector<Edge>> adjacency_list;
};

Graph::Graph() = default;

bool Graph::empty() const {
    return adjacency_list.empty();
}

bool Graph::has_node(Node node) const {
    return adjacency_list.find(node) != adjacency_list.end();
}

bool Graph::has_edge(Node from, Node to) {
    auto it = adjacency_list.find(from);
    if (it == adjacency_list.end()) return false;
    const auto& edges = it->second;
    for (const auto& edge : edges) {
        if (edge.to == to) return true;
    }
    return false;
}

void Graph::add_node(Node node) {
    if (!has_node(node)) {
        adjacency_list[node] = std::vector<Edge>();
    }
}

void Graph::remove_node(Node node) {
    if (!has_node(node)) throw std::invalid_argument("Node does not exist");
    adjacency_list.erase(node);
    for (auto& pair : adjacency_list) {
        std::vector<Edge> new_edges;
        for (const auto& edge : pair.second) {
            if (edge.to != node) {
                new_edges.push_back(edge);
            }
        }
        pair.second = std::move(new_edges);
    }
}

void Graph::add_edge(Node from, Node to, Weight weight) {
    if (!has_node(from) || !has_node(to)) throw std::invalid_argument("Node does not exist");
    auto& edges = adjacency_list.at(from);
    for (auto& edge : edges) {
        if (edge.to == to) {
            edge.weight = weight;
            return;
        }
    }
    edges.push_back({to, weight});
}

Graph::Weight Graph::remove_edge(Node from, Node to) {
    if (!has_node(from) || !has_node(to)) throw std::invalid_argument("Node does not exist");
    auto& edges = adjacency_list.at(from);
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it->to == to) {
            Weight w = it->weight;
            edges.erase(it);
            return w;
        }
    }
    throw std::invalid_argument("Edge does not exist");
}

std::vector<Graph::Node> Graph::nodes() const {
    std::vector<Node> result;
    for (const auto& pair : adjacency_list) {
        result.push_back(pair.first);
    }
    return result;
}

const std::vector<Graph::Edge>& Graph::edges_from(Node node) {
    auto it = adjacency_list.find(node);
    if (it == adjacency_list.end()) throw std::invalid_argument("Node does not exist");
    return it->second;
}

bool Graph::bellman_ford(Node source, std::unordered_map<Node, Weight>& dist, std::unordered_map<Node, Node>& prev) {
    if (!has_node(source)) throw std::invalid_argument("Source node does not exist");
    dist.clear();
    prev.clear();
    auto all_nodes = nodes();
    for (const auto& n : all_nodes) {
        dist[n] = std::numeric_limits<Weight>::max();
        prev[n] = -1;
    }
    dist[source] = 0;
    for (size_t i = 1; i < all_nodes.size(); ++i) {
        for (const auto& u : all_nodes) {
            auto it = adjacency_list.find(u);
            if (it == adjacency_list.end()) continue;
            const auto& edges = it->second;
            for (const auto& edge : edges) {
                Node v = edge.to;
                Weight w = edge.weight;
                if (dist[u] != std::numeric_limits<Weight>::max() && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                }
            }
        }
    }
    for (const auto& u : all_nodes) {
        auto it = adjacency_list.find(u);
        if (it == adjacency_list.end()) continue;
        const auto& edges = it->second;
        for (const auto& edge : edges) {
            Node v = edge.to;
            Weight w = edge.weight;
            if (dist[u] != std::numeric_limits<Weight>::max() && dist[u] + w < dist[v]) {
                return false;
            }
        }
    }
    return true;
}

#endif

