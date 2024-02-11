#include <iostream>
#include <time.h>
#include <queue>

using namespace std;

/* Calcular el numero de estados en cada profundidad usando BFS sin pruning */
/* y sin superar el limite de tiempo dado */

int main(int argc, char **argv) {
    time_t start, finish;
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

    // tiempo
    time(&start);
    time(&finish);
    minutes = atoi(argv[1]);

    // generar el estado inicial
    state_t first_goal_state;
    int d;
    first_goal_state(&first_goal_state, &d);
    // numero de estados en cada profundidad
    int64_t totalNodes = 1, temp = 0;

    printf("Profundidad |\tNumero de estados |\tFactor de ramificacion\n");

    state_t current_state, child;
    queue<state_t> bfsQueue;
    queue<state_t> children;
    int ruleid;
    ruleid_iterator_t iter;

    // agrego el estado inicial al queue 
    bfsQueue.push(first_goal_state);

    // mientras el queue no este vacio y el tiempo no se haya acabado
    while (!bfsQueue.empty() and difftime(finish, start)/60 < minutes) {
        // sacamos el primer elemento del queue
        current_state = bfsQueue.front();
        bfsQueue.pop();

        // Iteramos sobre cada hijo del estado actual
        init_bwd_iter(&iter, &current_state);
        while ((ruleid = next_ruleid(&iter)) >= 0) {
            // agregarlo al queue
            apply_bwd_rule(ruleid, &current_state, &child);
            children.push(child);
            totalNodes++;
        }

        // Verifica si todos los estados en una profundidad han sido visitados
        if (bfsQueue.empty()) {
            // visito los hijos de los estados en la profundidad actual
            bfsQueue = children;
            // vacio el queue de hijos
            children = queue<state_t>();

            // imprimo el # de profundidad, # de estados en esa profundidad y el factor de ramificacion
            printf("%d\t\t%"PRId64"\t\t\t%f\n", d, totalNodes, (float)totalNodes/(float)temp);
            temp = totalNodes;
            d++; // aumentar la profundidad a 1
        }
        time(&finish);
    }

    // imprimir el ultimo nivel y el numero total de estados encontrados 
    printf("%"PRIu64" estados en total.\n", totalNodes);

    return 0;
}
