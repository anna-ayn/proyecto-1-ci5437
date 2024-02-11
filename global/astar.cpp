#include <limits.h>
#include <iostream>
#include <chrono>
#include "priority_queue.hpp"

#define INFINITY INT_MAX

using namespace std;

int64_t nodes_expanded_for_initialstate;  // Cantidad de nodos expandidos dado un estado inicial

/*
Funcion que realiza la busqueda A*.
Recibe:
    - initial_state: el estado inicial
    - h: heuristica a utilizar
*/
int astar_search(state_t *initial_state, int (*h)(state_t*)){
    state_t state, child;
    int d, ruleid;
    ruleid_iterator_t iter;

    // Inicializamos el mapa de costos y la cola de prioridad para los estados generados
    state_map_t *map = new_state_map(); 
    PriorityQueue<state_t> q;
    // agregamos el estado inicial a la cola de prioridad
    q.Add(h(initial_state), 0, *initial_state);
    state_map_add(map, initial_state, 0);
    
    // Inicializamos el tiempo
    auto start = chrono::high_resolution_clock::now(), finish = chrono::high_resolution_clock::now();
    // Mientras la cola de prioridad no este vacia y no se haya terminado los 15 minutos de tiempo limite
    while (!q.Empty() && chrono::duration_cast<chrono::minutes>(finish - start).count() < 15){
        d = q.CurrentPriority();
        state = q.Top();
        q.Pop();

        // aumentar nodos expandidos
        nodes_expanded_for_initialstate++;

        // actualizamos el costo
        d -= h(&state);
        // si es el estado objetivo, terminamos
        if (is_goal(&state)) return d;
        
        // sino, verificar que el nodo actual no haya sido visitado
        int *aux = state_map_get(map, &state);
        // o si el costo es menor al costo previo
        if (aux == NULL || d <= *aux) {
            // expandemos el nodo
            // actualizamos el costo
            state_map_add(map, &state, d);

            // iteramos sobre los sucesores
            init_fwd_iter(&iter, &state);
            while ((ruleid = next_ruleid(&iter)) >= 0) {
                apply_fwd_rule(ruleid, &state, &child);

                // calculamos el costo del estado hijo
                int child_cost = h(&child); 
                if (child_cost < INT_MAX) {
                    // agregar el estado hijo al queue
                    int g = d + get_fwd_rule_cost(ruleid);
                    int f = g + child_cost;
                    q.Add(f, g, child);
                }
            }
        }
      // Actualizamos el tiempo
      finish = chrono::high_resolution_clock::now();
    }
    return -1;  // no se encontro la solucion
}

int main(int argc, char **argv) {
    char input[1024];
    state_t initial_state; 
    int n;

    open_pdbs();
    while (true) {
        if (fgets(input, sizeof input, stdin) == nullptr) return 0;
        n = read_state(input, &initial_state);
        if (n <= 0) {
            printf("El estado es invalido.\n");
            continue;
        }
        cout << "Estado inicial: " << input << endl;

        // Inicializamos el tiempo inicial
        auto start = chrono::high_resolution_clock::now();
        nodes_expanded_for_initialstate = 0;
        int ans = astar_search(&initial_state, heuristic);
        // Inicializamos el tiempo final
        auto end =  chrono::high_resolution_clock::now();
        // Calculamos el tiempo transcurrido
        chrono::duration<double> elapsed = end - start; 
        if (ans >= 0) {
          printf("Estado objetivo encontrado con distancia %d, nodos expandidos %ld, tiempo %f segundos.\n", ans, nodes_expanded_for_initialstate, elapsed.count());
        } else {
          printf("No se encontro el estado objetivo.\n");
          printf("Nodos expandidos %ld, tiempo %f segundos.\n", nodes_expanded_for_initialstate, elapsed.count());
        }
    }

    return 0;
}