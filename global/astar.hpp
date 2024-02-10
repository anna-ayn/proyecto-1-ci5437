#ifndef ASTAR_HPP
#define ASTAR_HPP


#include "../src/psvn.hpp"

typedef int Action;
typedef struct Node {
  state_t *state;
  struct Node *parent;
  Action action;  // ruleid
  unsigned g;     // cost of partial path
  int depth;

} Node;

using namespace std;

Node *astar_search(state_t *initial_state, int64_t *num_generated_states, int64_t *num_expanded_states,  int64_t *max_depth, int time_limit);

#endif  // ASTAR_HPP