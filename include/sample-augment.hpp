#ifndef __SAMPLE_AUGMENT_HPP_INCLUDED__
#define __SAMPLE_AUGMENT_HPP_INCLUDED__

#include<map>
#include<set>
#include"graph.hpp"
using namespace std;

typedef const pair<int,int> demand_pair;

typedef pair<demand_pair, double> demand;

typedef map<demand_pair, double> demands;

struct instance {
  int n;
  graph* G;
  double M;
  demands D;
  map<int,int> associate;

};

typedef graph solution;

typedef set<demand_pair*> sample;

solution sample_augment(instance*);

#endif
