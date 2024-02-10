#include "../src/psvn.cpp"
#include <limits.h>

#include <iostream>
#include <queue>
#include <unordered_map>

#define INFINITY UINT_MAX

using namespace std;

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
    time_t start, finish;
    time(&start);
    time(&finish);
    // Inicializamos el mapa de costos y la cola de prioridad
    unordered_map<string, unsigned> cost_so_far;  // visited,
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> q;
    // Inicializamos el nodo raiz y lo agregamos a la cola de prioridad
    Node *root = make_root_node(initial_state);
    q.push(make_pair(heuristic(initial_state), root));
    // Mientras la cola de prioridad no este vacia
    while (!q.empty() && difftime(finish, start) < time_limit){
        time(&finish);
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