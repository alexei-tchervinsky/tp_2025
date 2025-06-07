#ifndef GRAPH_TP_HPP
#define GRAPH_TP_HPP
#include <iostream>
#include <map>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <queue>
#include <numeric>
#include "DisjointSet_TP.hpp"

using namespace std;

struct Edge {
  int from_node;
  int target_node;
  int weight;

  Edge(int _u, int _v, int _w) : from_node(_u), target_node(_v), weight(_w) {}

  bool operator==(const Edge& e) const {
    return target_node == e.target_node;
  }

  bool operator>(const Edge& e) const {
    return weight > e.weight;
  }
  bool operator<(const Edge& e) const {
    return weight < e.weight;
  }
};

class Graph {
private:
    map<int, list<Edge>> adjList;

public:
    Graph() {};
    ~Graph() {};

    bool isEmpty() const;
    bool hasNode(int node) const;
    bool hasEdge(int u, int v) const;

    bool addNode(int node);
    bool addEdge(int u, int v, int weight);

    bool removeNode(int node);

    void printGraph() const;

    vector<Edge> getAllEdges();

    vector<int> findAllNode();

    const list<Edge>* getEdges(int u) const;

};

bool Graph::isEmpty() const {
    return adjList.empty();
};

bool Graph::hasNode(int node) const {
    return adjList.count(node) > 0;
};

bool Graph::hasEdge(int u, int v) const {
    if (!hasNode(u) || !hasNode(v)) {
        return false;
    }

    const auto& neighbours = adjList.at(u);
    return find_if(neighbours.begin(), neighbours.end(),
                   [&](const Edge& e) {
                     return e.target_node == v;}) != neighbours.end();
};

bool Graph::addNode(int node) {
    if (hasNode(node)) {
        cout << "Узел " << node << " уже существует." << endl;
        return false;
    }

    adjList[node] = list<Edge>();
    cout << "Узел " << node << " добавлен." << endl;
    return true;
};

bool Graph::addEdge(int u, int v, int weight) {
  if (!hasNode(u) || !hasNode(v)) {
    cout << "Один или оба узла не существуют." << endl;
    return false;
  };

  if (u == v) {
    cout << "Вершины одинаковые." << endl;
    return false;
  }

  if (hasEdge(u, v)) {
    cout << "Ребро уже существует." << endl;
    return false;
  }

  adjList[u].push_back(Edge(u, v, weight));
  adjList[v].push_back(Edge(v, u, weight));

  return true;
};

bool Graph::removeNode(int node) {
  if (!hasNode(node)) {
    cout << "Узел не существует." << endl;
    return false;
  }

  for (auto& pair : adjList) {
    pair.second.remove_if([&](const Edge& e) {return e.target_node == node;});
  };

  adjList.erase(node);
  return true;
};

void Graph::printGraph() const {
  if (isEmpty()) {
    cout << "Граф пустой." << endl;
    return;
  };
  cout << "Граф: " << endl;
  for (auto& pair : adjList) {
    cout << "Узел " << pair.first << ": ";
    if (pair.second.empty()) {
      cout << "(нет смежных узлов)" << endl;
    } else {
      for (auto& e : pair.second) {
        cout << "(узел: " << e.target_node << ", вес: " << e.weight << ") ";
      }
      cout << endl;
    }
  }
};

vector<Edge> Graph::getAllEdges() {
  vector<Edge> res;
  for (auto& pair : adjList) {
    int u = pair.first;
    for (auto& e : pair.second) {
      if (u < e.target_node) {
        res.push_back(e);
      }
    }
  }
  return res;
}

vector<int> Graph::findAllNode() {
  vector<int> res;
  for (auto& pair : adjList) {
    res.push_back(pair.first);
  }
  return res;
}

const std::list<Edge>* Graph::getEdges(int u) const {
  auto it = adjList.find(u);
  if (it != adjList.end()) {
    return &(it->second);
  }
  return nullptr;
}

Graph algorithmKruscala(Graph& graph) {
  if (graph.isEmpty()) {
    return graph;
  }

  Graph newGraph;
  vector<Edge> allEdges = graph.getAllEdges();

  if (allEdges.empty()) {
    return graph;
  }

  sort(allEdges.begin(), allEdges.end());

  DisjointSet ds;

  for (auto& e : allEdges) {
    int from = e.from_node;
    int to = e.target_node;
    int weight = e.weight;

    if (!ds.sameSet(from, to)) {
      newGraph.addNode(from);
      newGraph.addNode(to);
      newGraph.addEdge(from, to, weight);

      ds.unionSets(from, to);
    }
  }

  return newGraph;
};

Graph algorithmPrima(Graph& graph) {
  if(graph.isEmpty()) {
    return graph;
  }

  Graph newGraph;
  vector<int> nodes = graph.findAllNode();

  for (auto& node : nodes) {
    newGraph.addNode(node);
  }

  vector<int> visited;

  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
  visited.push_back(nodes[0]);

  const list<Edge>* edges = graph.getEdges(nodes[0]);
  if (edges) {
    for (auto& e : *edges) {
      pq.push(e);
    }
  }

  while (visited.size() < nodes.size() && !pq.empty()) {
    Edge min = pq.top();
    pq.pop();

    int u = min.from_node;
    int v = min.target_node;

    bool u_visited = find_if(visited.begin(), visited.end(), [&](int i) {
      return i == u;
    }) != visited.end();

    bool v_visited = find_if(visited.begin(), visited.end(), [&](int i) {
      return i == v;
    }) != visited.end();

    if (u_visited && v_visited) {
      continue;
    }

    int node_to_add;
    if (u_visited && !v_visited) {
      node_to_add = v;
    } else if (!u_visited && v_visited) {
      node_to_add = u;
    }

    visited.push_back(node_to_add);

    newGraph.addEdge(u, v, min.weight);

    const list<Edge>* edges = graph.getEdges(node_to_add);
    if (edges) {
      for (auto& e : *edges) {
        pq.push(e);
      }
    }
  }

  return newGraph;
};

#endif //GRAPH_TP_HPP
