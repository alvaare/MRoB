#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<vector>
using namespace std;

typedef pair<int, int> arc;

struct graph {
  int n;
  vector<arc>* edges;
  graph(int n) {
    this->n = n;
    this->edges = new vector<pair<int,int>>[n];
  }
  ~graph() {
    delete [] this->edges;
  }
};


#endif
