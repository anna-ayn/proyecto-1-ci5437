#include <string>
#include <vector>

using namespace std;

// Variables globales
int rows[16]; 
int columns[16];


/*
    Funcion que abre los PDBs y los almacena en el vector
*/
void open_pdbs() {
    for (int i = 0; i < 16; i++) {
        rows[i] = i / 4;
        columns[i] = i % 4;
    }
}

/*
    Funcion que calcula el valor heuristico de un estado con la distancia de Manhattan
    Recibe:
        - state: el estado al que se le calculara el valor heuristico
    Retorna:
        Retorna el valor heuristico del estado
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