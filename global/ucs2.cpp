#include <time.h>
#include <vector>
#include "priority_queue.hpp"

using namespace std;

// Definir el estado y el historial de un nodo del grafo
class Node {
  public:
    state_t state;
    int hist;

    Node(state_t state, int hist) {
        this->state = state;
        this->hist = hist;
    }
};

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
    int d, ruleid;
    ruleid_iterator_t iter;
    state_t first_goal_state;

    first_goal_state(&first_goal_state, &d);

    PriorityQueue<Node> open; // used for the states we have generated but not yet expanded (the OPEN list)
    state_map_t *map = new_state_map(); // contains the cost-to-goal for all states that have been generated
    FILE *file; // the final state_map is written to this file if it is provided (command line argument)

    Node current_state = Node(first_goal_state, init_history), child = Node(first_goal_state, init_history);
    
    open.Add(0, 0, current_state);

    do {
        state_map_add(map, &current_state.state, 0);
        open.Add(0, 0, current_state);
    } while( next_goal_state(&current_state.state, &d) );

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
        current_state = open.Top();
        open.Pop();

        numAtD++;
        totalNodes++;

        
        // look at all predecessors of the state
        init_bwd_iter(&iter, &current_state.state);
        while( (ruleid = next_ruleid(&iter) ) >= 0 ) {
            if (bwd_rule_valid_for_history(current_state.hist, ruleid) == 0) {
                continue;
            }
            
            apply_bwd_rule(ruleid, &current_state.state, &child.state);
            const int child_d = d + get_bwd_rule_cost(ruleid);

            state_map_add(map, &child.state, child_d);
            child.hist = next_bwd_history(child.hist, ruleid);
            open.Add(child_d, child_d, child);
            
        }
        time(&finish);
    }
    // print last level and total states
    if( numAtD > 0 ) {
        printf("%"PRId64" estados en la profundidad %d\n", numAtD, d);
    }
    printf("%"PRIu64" estados en total.\n", totalNodes);

    return 0;
}
