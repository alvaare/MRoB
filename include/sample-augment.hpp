#ifndef __SAMPLE_AUGMENT_HPP_INCLUDED__
#define __SAMPLE_AUGMENT_HPP_INCLUDED__

#include<map>
#include<set>
#include"graph.hpp"
using namespace std;

struct demand_pair {
  int s;
  int t;
  int d;
};

struct instance {
  int n;
  graph G;
  int M;
  set<demand_pair> D;
  map<demand_pair, int> w;
};

#endif
