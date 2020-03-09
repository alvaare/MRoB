#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<set>
using namespace std;

typedef pair<int, int> edge;

struct graph {
  int n;
  set<int>* neighbors;
  double** distance;

  graph(int n);
  ~graph();
  void add_edge(int, int, double);
  void print();
  bool is_edge(int, int);
};


#endif
