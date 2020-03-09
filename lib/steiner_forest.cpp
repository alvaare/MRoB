#include<unordered_set>
#include"steiner_forest.hpp"

bool moat::operator==(const moat other) const {
  return nodes==other.nodes;
}

class hash_of_moat {
  public:
    size_t operator()(moat const& M) const {
      return *M.nodes.begin();
    }
};

typedef unordered_set<moat, hash_of_moat> set_of_moats;

moat construct_moat(int s, graph* G) {
  set<int> nodes = {s};
  set<edge> out_edges;
  for (auto e : G->neighbors[s])
    out_edges.insert({s, e});
  return {nodes, out_edges};
}

set_of_moats initialize_moats(graph* G, sample* S) {
  set_of_moats active_moats;
  for (auto g : *S) {
    active_moats.insert(construct_moat(g->first, G));
    active_moats.insert(construct_moat(g->second, G));
  }
  return active_moats;
}

void steiner_forest(graph* G, sample* S, solution* T) {
  set_of_moats active_moats = initialize_moats(G, S);
}
