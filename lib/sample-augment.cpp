#include<random>
#include<iostream>
#include"sample-augment.hpp"
using namespace std;

set<demand_pair*> random_sampling(instance* P) {
  set<demand_pair*> S;
  for(auto dp : P->D) {
    double p = P->w[&dp]/P->M;
    if (p>1)
      p=1;
    if ((double)rand()/RAND_MAX < p)
      S.insert(&dp);
  }
  return S;
}

solution sample_augment(instance* P) {
  set<demand_pair*> S = random_sampling(P);
  solution G(P->n);
  //subproblem step
  //steiner_forest(P, &S, &G);
  //augmentation step
  //augmentation(P, &S, &G);
  return G;
}
