#include <iostream>
#include <algorithm>
#include <utility> 

using namespace std;

struct Node {
  public:
    state_t state; // Estado representado por un nodo 

    Node *parent; // Nodo padre
    unsigned g; // costo del camino parcial 

    // constructor
    Node(state_t state, Node *parent, unsigned g) {
        this->state = state;
        this->parent = parent;
        this->g = g;
    }
};

// Variables globales
unsigned long int nodes_expanded_for_initialstate;  // cantidad de nodos expandidos dado un estado inicial

/*
    Funcion que realiza DFS con una profundidad de limite en un nodo dado
    Recibe:
        - n: el nodo para comenzar la busqueda
        - bound: el valor f maximo permitido para un nodo
        - hist: el historial de aplicaciones de reglas
        - h: una funcion heuristica para estimar el costo de un nodo al objetivo
    Retorna:
        Retorna un par que contiene el nodo objetivo y su costo de camino si se encuentra dentro del limite,
        sino un par con un nullptr y el valor f del nodo que excedio el limite.
*/
pair<Node *, unsigned> f_bounded_dfs_visit(Node *n, unsigned bound, int hist, int (*h)(state_t*)) {
    state_t child;
    int ruleid;
    unsigned t;
    ruleid_iterator_t iter;

    // Caso base
    unsigned f = n->g + h(&n->state);
    if (f > bound) return make_pair(nullptr, f);
    if (is_goal(&n->state)) return make_pair(n, n->g);

    // t = INFINITY
    t = INT_MAX;
    nodes_expanded_for_initialstate++;
    init_fwd_iter(&iter, &n->state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid, &n->state, &child);

        // si el estado ya fue visitado, lo ignoramos
        if (!fwd_rule_valid_for_history(hist, ruleid)) continue;

        // crear un nuevo nodo para el hijo
        Node m(child, n, n->g + get_fwd_rule_cost(ruleid));

        // Visitar el nodo hijo
        pair<Node *, unsigned> p = f_bounded_dfs_visit(&m, bound, next_fwd_history(hist, ruleid), h);
        if (p.first != nullptr) return p;
        t = min(t, p.second);
    }

    return make_pair(nullptr, t);
}

/*
    Funcion que realiza la busqueda IDA*
    Recibe:
        - initial_state: el estado inicial
        - heuristic: la heuristica a utilizar
    Retorna:
        - El nodo objetivo
*/
Node ida_star(state_t *initial_state, int (*h)(state_t*)) {
    Node root(*initial_state, nullptr, 0);
    pair<Node *, unsigned> p;
    unsigned long int bound = h(initial_state);

    // Buscar con límites crecientes del valor f
    while (true) {
        printf("Explorando con límite de profundidad %ld\n", bound);
        p = f_bounded_dfs_visit(&root,bound, init_history, h);
        if (p.first != nullptr) return *p.first;
        bound = p.second;
    }
}

int main(int argc, char **argv) {
    time_t start, finish;
    char input[1024];
    state_t initial_state; 
    int n;

    init_heuristic();
    while (true) {
        if (fgets(input, sizeof input, stdin) == nullptr) return 0;
        n = read_state(input, &initial_state);
        if (n <= 0) {
            printf("El estado es invalido.\n");
            continue;
        }
        cout << "Estado inicial: " << input << endl;

        // Inicializamos el tiempo inicial
        time(&start);
        nodes_expanded_for_initialstate = 0;
        Node node = ida_star(&initial_state, heuristic);
        // Inicializamos el tiempo final
        time(&finish);
        // Calculamos el tiempo transcurrido
        double time_elapsed = difftime(finish, start);

        printf("Estado objetivo encontrado con distancia %d, nodos expandidos %ld, tiempo %f\n", node.g, nodes_expanded_for_initialstate, time_elapsed);
    }

    return 0;
}