#include<iostream>
#include<climits>
#include"graph.hpp"

graph::graph(int n) {
  this->n = n;
  this->neighbors = new set<int>[n];
  this->distance = new double*[n];
  for (int i=0; i<n; i++) {
    this->distance[i] = new double[n];
    for (int j=0; j<n; j++)
      this->distance[i][j] = INT_MAX;
  }
}

graph::~graph() {
  delete [] this->neighbors;
  for (int i=0; i<this->n; i++)
    delete [] this->distance[i];
  delete [] this->distance;
}

void graph::add_edge(int u, int v, double w) {
  neighbors[u].insert(v);
  neighbors[v].insert(u);
  distance[u][v] = w;
  distance[v][u] = w;
}

void graph::print() {
   for (int u=0; u<n; u++) {
     cout << u << ": ";
     for (auto v : neighbors[u]) {
       cout << "(" << v << ", " << distance[u][v] << ") ";
     }
     cout << "\n";
   }
}

bool graph::is_edge(int u, int v) {
  return distance[u][v] != INT_MAX;
}

bool graph::connected(int u) {
  return !neighbors[u].empty();
}

graph graph::copy() {
  graph G(n);
  for (int i=0; i<n; i++) {
    G.neighbors[i] = neighbors[i];
    for (int j=0; j<n; j++)
      G.distance[i][j] = distance[i][j];
  }
  return G;
}
