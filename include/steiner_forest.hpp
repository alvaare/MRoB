#ifndef __STEINER_FOREST_HPP_INCLUDED__
#define __STEINER_FOREST_HPP_INCLUDED__

#include"graph.hpp"
#include"sample-augment.hpp"

struct moat {
  set<int> nodes;
  set<edge> out_edges;

  bool operator==(const moat) const;
  size_t operator()(moat);
};

void steiner_forest(instance, sample*, solution);

#endif
