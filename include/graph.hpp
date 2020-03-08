#ifndef __GRAPH_HPP_INCLUDED__
#define __GRAPH_HPP_INCLUDED__

#include<vector>
using namespace std;

struct graph {
  int n;
  vector<pair<int,int>>* edges;
  graph(int n) {
    this->n = n;
    this->edges = new vector<pair<int,int>>[n];
  }
  ~graph() {
    delete [] this->edges;
  }
};


#endif
