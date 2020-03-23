#ifndef __STEINER_FOREST_HPP_INCLUDED__
#define __STEINER_FOREST_HPP_INCLUDED__

#include"graph.hpp"
#include"sample-augment.hpp"

struct aux_graph {
  graph G;
  map<int, set<int>> aux_nodes;
  map<int, int> father;
  map<edge, edge> memory_edge;
  set<int> active_nodes;

  set<int>* from_node_to_set(int);
};

struct aux_node {
  int id;
  double dual_value = 0;

  bool operator<(const aux_node) const;
};

void steiner_forest(instance, sample*, solution);

#endif
