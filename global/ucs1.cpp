#include <time.h>
#include <vector>
#include "priority_queue.hpp"

using namespace std;

int main(int argc, char **argv) {
    time_t start, finish;
    int minutos;

    if (argc < 2){
        printf("Por favor introduce la cantidad de minutos de la siguiente forma:\n");
        printf("./<nombre del archivo>.ucs1 <limite de minutos>\n");
        printf("Por ejemplo: ./15-puzzle 10\n");
        return 0;
    }
    if (atoi(argv[1])<=0){
        printf("La cantidad de minutos debe ser mayor a 0 (cero)\n");
        return 0;
    }

    time(&start);
    time(&finish);
    minutos = atoi(argv[1]);

    int64_t temp;
    int64_t totalNodes, numAtD;  // counters
    state_t state, child;   // NOTE: "child" will be a predecessor of state, not a successor
    int d, ruleid;
    ruleid_iterator_t iter;

    PriorityQueue<state_t> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated

    // add goal states
    first_goal_state(&state, &d);
    do {
        state_map_add(map, &state, 0);
        open.Add(0, 0, state);
    } while( next_goal_state(&state, &d) );

    d = 0;
    numAtD = 0;
    totalNodes = 0;
    temp = 0;
    printf("Profundidad |\tNumero de estados |\tFactor de ramificacion\n");

    while( !open.Empty() and difftime(finish, start)/60 < minutos ) {
        // get current distance from goal; since operator costs are
        // non-negative this distance is monotonically increasing
        if( open.CurrentPriority() > d ) {
            printf("%d\t\t%"PRId64"\t\t%f\n", d, numAtD, (float)numAtD/(float)temp);
            d = open.CurrentPriority();
            temp = numAtD;
            numAtD = 0;
        }

        // remove top state from priority state
        state = open.Top();
        open.Pop();

        numAtD++;
        totalNodes++;

        time(&finish);
        if ((difftime(finish,start)/60)<minutos){
            // look at all predecessors of the state
            init_bwd_iter(&iter, &state);
            while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
                apply_bwd_rule(ruleid, &state, &child);
                const int child_d = d + get_bwd_rule_cost(ruleid);

                state_map_add(map, &child, child_d);
                open.Add(child_d, child_d, child);
            }
        }
    }
    
    // print last level and total states
    if( numAtD > 0 ) {
        printf("%"PRId64" estados en la profundidad %d\n", numAtD, d);
    }
    printf("%"PRIu64" estados en total.\n", totalNodes);

    
    return 0;
}
