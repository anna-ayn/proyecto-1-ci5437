#include <iostream>
#include <time.h>
#include <queue>

using namespace std;

/* Una funcion que realiza el DFS hasta una profundidad dada 
    Recibe:
        state: un punteor al estado de origen
        d: la profundidad actual
        bound: la profundidad maxima a visitar
        totalNodes: un puntero a la cantidad de estados visitados
*/
void dls(state_t *state, int d, int bound, int64_t *totalNodes, int hist) {
    state_t child;
    int ruleid;
    ruleid_iterator_t iter;

    // aumentar el numero de estados visitados
    *totalNodes = *totalNodes + 1;

    // si ya alcanzamos el limite de profundidad, terminar
    if (d == bound) 
        return;

    // iterar sobre cada hijo del estado actual
    init_bwd_iter(&iter, state);
    while ((ruleid = next_ruleid(&iter)) >= 0) {
        if (!bwd_rule_valid_for_history(hist, ruleid)) 
            continue;

        apply_bwd_rule(ruleid, state, &child);
        dls(&child, d + 1, bound, totalNodes, next_bwd_history(hist, ruleid));
    }
}


/* Calcular el numero de estados en cada profundidad usando IDDFS sin pruning */
/* y sin superar el limite de tiempo dado */

int main(int argc, char **argv) {
    time_t start, finish;
    int minutes;

    if (argc < 2){
        printf("Por favor introduce la cantidad de minutos de la siguiente forma:\n");
        printf("./<nombre del archivo>.iddfs1 <limite de minutos>\n");
        printf("Por ejemplo: ./15-puzzle.iddfs2 15\n");
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
    int64_t totalNodes = 0;
    // inicializar el bound en 1 para el iddfs
    int bound = 1;

    printf("Profundidad |\tNumero de estados |\tFactor de ramificacion\n");

    int64_t temp = 0;
    // mientras el tiempo no se haya acabado
    while(difftime(finish, start)/60 < minutes) {
        int hist = init_history;
        // visitar el estado inicial y sus hijos hasta la profundidad dada
        dls(&first_goal_state, 0, bound, &totalNodes, hist);

        // imprimir el numero de estados visitados en cada profundidad
        printf("%d\t\t%"PRId64"\t\t\t%f\n", bound, totalNodes, (float)totalNodes/(float)temp);

        // aumentar el bound y reiniciar el numero de estados visitados
        bound++;
        temp = totalNodes;
        totalNodes = 0;
        time(&finish);
    }

    // imprimir el ultimo nivel y el numero total de estados encontrados 
    printf("%"PRIu64" estados en total.\n", totalNodes);

    return 0;
}