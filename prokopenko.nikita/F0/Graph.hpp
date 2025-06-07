#pragma once

#include "GraphExceptions.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>

class Graph {
private:
    std::vector<std::vector<int>> adj;
    std::unordered_map<std::string, int> name_to_index;
    std::vector<std::string> index_to_name;

    void dfs_until(int v, std::vector<bool>& visited) const {
        visited[v] = true;
        std::cout << index_to_name[v] << " ";
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                dfs_until(neighbor, visited);
            }
        }
    }

    void topsort_util(int v, std::vector<bool>& visited, std::vector<std::string>& sorted) const {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                topsort_util(neighbor, visited, sorted);
            }
        }
        sorted.push_back(index_to_name[v]);
    }

    bool dfs_cycle(int v, std::vector<bool>& visited, std::vector<bool>& rec_stack) const {
        visited[v] = rec_stack[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor] && dfs_cycle(neighbor, visited, rec_stack)) return true;
            if (rec_stack[neighbor]) return true;
        }
        rec_stack[v] = false;
        return false;
    }

    bool has_cycle() const {
        std::vector<bool> visited(adj.size(), false);
        std::vector<bool> rec_stack(adj.size(), false);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (!visited[i] && dfs_cycle(i, visited, rec_stack)) return true;
        }
        return false;
    }

public:
    Graph() = default;

    bool has_vertex(const std::string& name) const {
        return name_to_index.contains(name);
    }

    void add_vertex(const std::string& name) {
        if (has_vertex(name)) throw VertexAlreadyExist(name);
        name_to_index[name] = static_cast<int>(adj.size());
        index_to_name.push_back(name);
        adj.emplace_back();
    }

    void remove_vertex(const std::string& name) {
        if (!has_vertex(name)) throw VertexDontExist(name);

        int index = name_to_index[name];

        for (auto& neighbors : adj) {
            neighbors.erase(std::remove(neighbors.begin(), neighbors.end(), index), neighbors.end());
            for (auto& v : neighbors) {
                if (v > index) --v;
            }
        }

        adj.erase(adj.begin() + index);
        index_to_name.erase(index_to_name.begin() + index);

        name_to_index.clear();
        for (size_t i = 0; i < index_to_name.size(); ++i) {
            name_to_index[index_to_name[i]] = static_cast<int>(i);
        }
    }

    void add_edge(const std::string& from, const std::string& to) {
        if (!has_vertex(from) || !has_vertex(to)) throw CantAddEdge(from, to);

        int u = name_to_index[from];
        int v = name_to_index[to];

        if (std::find(adj[u].begin(), adj[u].end(), v) != adj[u].end()) {
            throw EdgeAlreadyExist(from, to);
        }

        adj[u].push_back(v);
    }

    void print() const {
        for (size_t i = 0; i < adj.size(); ++i) {
            std::cout << index_to_name[i] << ": ";
            for (int j : adj[i]) {
                std::cout << index_to_name[j] << " ";
            }
            std::cout << "\n";
        }
    }

    void dfs(const std::string& start_name) const {
        if (!has_vertex(start_name)) throw VertexDontExist(start_name);

        int start = name_to_index.at(start_name);
        std::vector<bool> visited(adj.size(), false);

        std::cout << "DFS from " << start_name << ": ";
        dfs_until(start, visited);
        std::cout << "\n";
    }

    void SuperDfs() const {
        std::vector<bool> visited(adj.size(), false);
        std::cout << "SUPER DFS:\n";
        for (size_t i = 0; i < adj.size(); ++i) {
            if (!visited[i]) dfs_until(i, visited);
        }
        std::cout << "\n";
    }

    void Topsort() const {
        if (has_cycle()) {
            throw GraphHasCycle();
        }

        std::vector<std::string> sorted;
        std::vector<bool> visited(adj.size(), false);

        for (size_t i = 0; i < adj.size(); ++i) {
            if (!visited[i]) topsort_util(i, visited, sorted);
        }

        std::reverse(sorted.begin(), sorted.end());

        std::cout << "TOP SORT:\n";
        for (const auto& name : sorted) {
            std::cout << name << " ";
        }
        std::cout << "\n";
    }
};
