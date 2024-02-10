#include <string>
#include <vector>

using namespace std;

// Global variables to store 
int rows[16]; 
int columns[16];

/**
 * Opens the PDBs and stores them in the global variables
 */
void init_heuristic() {
    for (int i = 0; i < 16; i++) {
        rows[i] = i / 4;
        columns[i] = i % 4;
    }
}

/**
 * Computes the heuristic value of a state
 * Manhattan distance
 * @param state The state to compute the heuristic value
 * @return The heuristic value of the state
 */
int heuristic(state_t *state) {
    int h, size = 16;
	var_t *vals = state->vars;

    h = 0;
    for (int i = 0; i < size; i++) {
        int n = vals[i];
        if (n == 0) continue;

        int x = i / 4;
        int y = i % 4;
        int x_goal = rows[n];
        int y_goal = columns[n];
        h += abs(x - x_goal) + abs(y - y_goal);
    }

    return h;
}