#include<unordered_set>
#include<climits>
#include<queue>
#include<vector>
#include<iostream>
#include"steiner_forest.hpp"

const double EPS = 1e-04;

bool aux_node::operator<(const aux_node other) const {
  return dual_value < other.dual_value;
}

set<int>* aux_graph::from_node_to_set(int u) {
  return &aux_nodes[u];
}

aux_graph construct_aux_graph(graph* G, sample* S) {
  map<int, set<int>> aux_nodes;
  for (int i=0; i<G->n; i++)
    aux_nodes.insert({i,{i}});
  set<int> active_nodes;
  for (auto dp : *S) {
    active_nodes.insert(dp->first);
    active_nodes.insert(dp->second);
  }
  return {G->copy(), aux_nodes, {}, {}, active_nodes};
}

double find_tau(aux_graph* A) {
  int n = A->G.n;
  double distance[n][n];
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      distance[i][j] = A->G.distance[i][j];
  for (int k=0; k<n; k++)
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        if (distance[i][j]>distance[i][k]+distance[k][j])
          distance[i][j] = distance[i][k]+distance[k][j];
  double min_tau = INT_MAX;
  for (int i=0; i<n; i++)
    for (int j=0; j<n; j++)
      if (distance[i][j] < min_tau)
        min_tau = distance[i][j];
  return min_tau/2;
}

typedef priority_queue<aux_node> aux_pq;

void merge_nodes(int active, int u, aux_graph* A) {
  A->aux_nodes[active].insert(A->aux_nodes[u].begin(), A->aux_nodes[u].end());
}

edge find_real_edge(int u, int v, aux_graph* A) {
  edge real = {u, v};
  if (A->memory_edge.find({u,v}) != A->memory_edge.end())
    real = A->memory_edge[{u,v}];
  return real;
}

void remember_edge(int u, int v, int a, aux_graph* A) {
  edge out = find_real_edge(u, v, A);
  edge in = {out.second, out.first};
  A->memory_edge[{a,v}] = out;
  A->memory_edge[{v,a}] = in;
}

void include_node(int u, int a, aux_graph* A) {
  merge_nodes(a, u, A);
  A->father[u] = A->memory_edge[{a, u}].first;
  for (auto v: A->G.neighbors[u]) {
    A->G.neighbors[v].erase(u);
    A->G.neighbors[a].insert(v);
    if (A->G.distance[u][v] < A->G.distance[a][v]) {
      A->G.distance[a][v] = A->G.distance[u][v];
      A->G.distance[v][a] = A->G.distance[v][u];
      remember_edge(u, v, a, A);
    }
  }
}

void process_node(aux_node* a, aux_pq* pq, aux_graph* A, int state[]) {
  for (auto v : A->G.neighbors[a->id]) {
    double edge_dist = A->G.distance[a->id][v];
    if (edge_dist > a->dual_value) {
      A->G.distance[a->id][v] -= a->dual_value;
      A->G.distance[v][a->id] -= a->dual_value;
    }
    else
      if (state[v] != -1 && state[v] < a->dual_value-edge_dist) {
        pq->push({v, a->dual_value-edge_dist});
        state[v] = a->dual_value-edge_dist;
      }
  }
  if (A->father.find(a->id)!=A->father.end())
    include_node(a->id, A->father[a->id], A);
}

void propagate_from_active_node(int u, aux_graph* A, double tau) {
  int n = A->G.n;
  int state[n] = {0}; //0:not seen   p>0:dual value if pending   -1:propagated
  aux_pq pq;
  pq.push({u, tau});
  state[u] = tau;
  while (!pq.empty()) {
    aux_node a = pq.top();
    pq.pop();
    if (state[a.id] > 0)
      process_node(&a, &pq, A, state);
    state[a.id] = -1;
  }
}

void update_aux_graph(aux_graph* A, double tau) {
  for (auto u : A->active_nodes) {
    propagate_from_active_node(u, A, tau);
  }
}

void add_edge(edge e, graph* G, solution* T) {
  double distance = G->distance[e.first][e.second];
  T->add_edge(e.first, e.second, distance);
}

bool contains(set<int>* S, int i) {
  return S->find(i) != S->end();
}

bool is_in_T(int u, solution* T, aux_graph* A) {
  return contains(&A->active_nodes, u) || !T->neighbors[u].empty();
}

void connect(int b, graph* G, solution* T, aux_graph* A) {
  int current_node = b;
  while (!is_in_T(current_node, T, A)) {
    int f = A->father[current_node];
    edge e = find_real_edge(current_node, f, A);
    add_edge(e, G, T);
    current_node = f;
  }
}

void repair_collisions(graph* G, aux_graph* A, solution* T) {
  int n = A->G.n;
  for (int i=0; i<n; i++)
    for (int j=i+1; j<n; j++) {
      if (A->G.distance[i][j]==0) {
        edge e = find_real_edge(i, j, A);
        add_edge(e, G, T);
        connect(e.first, G, T, A);
        connect(e.second, G, T, A);
        include_node(j, i, A);
      }
    }
}

void steiner_forest(graph* G, sample* S, solution* T) {
  aux_graph A = construct_aux_graph(G, S);
  while (!A.active_nodes.empty()) {
    double tau = find_tau(&A);
    update_aux_graph(&A, tau);
    repair_collisions(G, &A, T);
  }
}
