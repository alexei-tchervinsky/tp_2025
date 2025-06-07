#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP
#include <iostream>
#include <vector>

class DisjointSet {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  DisjointSet(int size = 1000) {
    for (size_t i = 0; i < size; ++i) {
      parent.push_back(i);
      rank.push_back(0);
    }
  }
  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }
  void unionSets(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);

    if (xroot != yroot) {
      if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
      } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
      } else {
        parent[yroot] = xroot;
        rank[xroot]++;
      }
    }
  }
  bool sameSet(int x, int y) {
    return find(x) == find(y);
  }
};

#endif
