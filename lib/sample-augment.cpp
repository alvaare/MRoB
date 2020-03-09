#include<random>
#include<iostream>
#include"sample-augment.hpp"
using namespace std;

sample random_sample(instance* P) {
  sample S;
  for(auto d : P->D) {
    double p = d.second/P->M;
    if (p>1)
      p=1;
    if ((double)rand()/RAND_MAX < p) {
      S.insert(&(d.first));
    }
  }
  return S;
}

solution sample_augment(instance* P) {
  sample S = random_sample(P);
  solution F(P->n);
  //subproblem step
  //steiner_forest(&P->G, &S, &F);
  //augmentation step
  //augmentation(P, &S, &F);
  return F;
}
