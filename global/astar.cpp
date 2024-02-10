#include <limits.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include "astar.hpp"

#define INFINITY UINT_MAX

using namespace std;

Node *make_root_node(state_t *state) {
  Node *node = new Node;
  node->state = state;
  node->parent = NULL;
  node->action = -1;
  node->g = 0;
  node->depth = 0;
  return node;
}

Node *make_node(Node *parent, state_t *state, Action action) {
  Node *node = new Node;
  node->state = state;
  node->parent = parent;
  node->action = action;
  node->g = parent->g + get_fwd_rule_cost(action);
  node->depth = parent->depth + 1;
  return node;
}

vector<pair<state_t *, Action>> *successors(state_t *state) {
  vector<pair<state_t *, Action>> *successors_list =
      new vector<pair<state_t *, Action>>;
  if (successors_list == NULL) {
    fprintf(stderr, "out of memory\n");
    return NULL;
  }
  ruleid_iterator_t *iter = new ruleid_iterator_t;
  if (iter == NULL) {
    fprintf(stderr, "out of memory\n");
    return NULL;
  }
  int move_cost, ruleid;
  int hist, child_hist;
  hist = init_history;
  init_fwd_iter(iter, state);
  while ((ruleid = next_ruleid(iter)) >= 0) {
    if (!fwd_rule_valid_for_history(hist, ruleid)) {
      continue;
    }
    state_t *child = (state_t *)(malloc(sizeof(state_t)));
    if (child == NULL) {
      fprintf(stderr, "out of memory\n");
      return NULL;
    }
    child_hist = next_fwd_history(hist, ruleid);
    apply_fwd_rule(ruleid, state, child);
    // oprint_state(child);
    //     move_cost = get_fwd_rule_cost(ruleid);
    successors_list->push_back(make_pair(child, ruleid));
  }
  return successors_list;
}

void set_distance(state_t *state, unsigned distance, unordered_map<string, unsigned> &cost_so_far) {
  char *str_state = new char[1024];
  sprint_state(str_state, 1024, state);
  cost_so_far[string(str_state)] = distance;
}

unsigned get_distance(state_t *state, unordered_map<string, unsigned> &cost_so_far) {
  char *str_state = new char[1024];
  sprint_state(str_state, 1024, state);
  // detect if the state is not in the map
  if (cost_so_far.find(string(str_state)) == cost_so_far.end()) {
    return UINT_MAX;
  }
  unsigned r = cost_so_far[string(str_state)];
  return r;
}

/*
Funcion que realiza la busqueda A*.
Recibe:
    - initial_state: el estado inicial
    - num_generated_states: el numero de estados generados
    - num_expanded_states: el numero de estados expandidos
    - max_depth: la profundidad maxima
    - time_limit: el limite de tiempo
*/
Node *astar_search(state_t *initial_state, int64_t *num_generated_states, int64_t *num_expanded_states,  int64_t *max_depth, int time_limit){
    // Inicializamos el tiempo
    auto start = chrono::high_resolution_clock::now(), finish = chrono::high_resolution_clock::now();
    // Inicializamos el mapa de costos y la cola de prioridad
    unordered_map<string, unsigned> cost_so_far;  // visited,
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> q;
    // Inicializamos el nodo raiz y lo agregamos a la cola de prioridad
    Node *root = make_root_node(initial_state);
    q.push(make_pair(heuristic(initial_state), root));
    // Mientras la cola de prioridad no este vacia y no se haya terminado el tiempo
    while (!q.empty() && chrono::duration_cast<chrono::minutes>(finish - start).count() < time_limit){
        // Sacamos el nodo con menor costo de la cola de prioridad
        Node *n = q.top().second;
        q.pop();
        // Si el nodo no ha sido visitado o el costo es menor al costo previo
        state_t *ns = n->state;
        if (n->g < get_distance(ns, cost_so_far)) {
            // Actualizamos el costo
            set_distance(ns, n->g, cost_so_far);
            // Si el nodo es una meta, terminamos
            if (is_goal(ns)) {
                printf("Solution found!\n");
                return n;
            }
            vector<pair<state_t *, Action>> *successors_list = successors(ns);
            // Expandemos el nodo
            (*num_expanded_states)++;
            
            printf("Expanded: %ld\n", *num_expanded_states);
            // Por cada sucesor
            for (auto successor : *successors_list) {
                // Si el costo es finito
                if (heuristic(successor.first) < INFINITY) {
                    // Creamos un nodo hijo y lo agregamos a la cola de prioridad
                    Node *child = make_node(n, successor.first, successor.second);
                    // Actualizamos el costo
                    int max_d = *max_depth;
                    (*max_depth) = max(max_d, child->depth);
                    // Agregamos el nodo a la cola de prioridad
                    q.push(make_pair(child->g + get_fwd_rule_cost(successor.second) + heuristic(child->state), child));
                    // Actualizamos el numero de nodos generados
                    (*num_generated_states)++;
                }
            }
        }
        // Actualizamos el tiempo
        finish = chrono::high_resolution_clock::now();
    }
  return nullptr;  // no solution found
}

int main(int argc, char **argv) {
    int minutes;

    if (argc < 2){
        printf("Por favor introduce la cantidad de minutos de la siguiente forma:\n");
        printf("./<nombre del archivo>.bfs1 <limite de minutos>\n");
        printf("Por ejemplo: ./15-puzzle.bfs1 15\n");
        return 0;
    }
    if (atoi(argv[1])<=0){
        printf("La cantidad de minutos debe ser mayor a 0 (cero)\n");
        return 0;
    }
    minutes = atoi(argv[1]);

    // generar el estado inicial
    state_t first_goal_state;
    int d;
    first_goal_state(&first_goal_state, &d);
    // numero de estados en cada profundidad
    int64_t totalNodes = 1, temp = 0;

    printf("Profundidad |\tNumero de estados |\tFactor de ramificacion\n");

    Node* result = astar_search(&first_goal_state, &totalNodes, &temp, &temp, minutes);
    return 0;
}