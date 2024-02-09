#include <vector>
#include <string>
using namespace std;

// Vectores que guardan los PDBs y abstracciones
vector<abstraction_t*> absts;
vector<state_map_t*> state_maps;


/*
    Funcion que abre los PDBs y los almacena en el vector
*/
void init_heuristic() {
    // tenemos 3 PDBs
	vector<string> filepdbs = {"15-puzzle_test1.pdb"};
    vector<string> fileabsts = {"15-puzzle_test1.abst"};

    // itero en cada archivo PDB
	for (unsigned int i = 0; i < filepdbs.size(); i++) {
        // abro el archivo
		FILE *filepdb = fopen((filepdbs[i]).c_str(), "r");
        // verifico que no este vacio el archivo
		if (filepdb == NULL) {
			printf("El archivo PDB es invalido.\n");
			return;
		}
        // guardo el PDB y la abstraccion en los vectores, y cierro el archivo
		state_maps.push_back(read_state_map(filepdb));
		fclose(filepdb);
		absts.push_back(read_abstraction_from_file((fileabsts[i]).c_str()));

        // verifico si las abstracciones y los pdbs son validas
		if (state_maps[i] == NULL) {
			printf("El archivo PDB es invalido.\n");
			state_maps.pop_back();
		}

        if (state_maps[i] == NULL) {
            printf("El archivo de abstraccion es invalido.\n");
            absts.pop_back();
        }
	}
}


/*
    Funcion que calcula el valor heuristico de un estado para PDBs aditivos
    Recibe:
        - state: el estado al que se le calculara el valor heuristico
    Retorna:
        Retorna el valor heuristico del estado
*/
int heuristic(state_t *state) {
    long long int sum = 0;
	state_t *aux_state = new state_t;

	// calcular el valor heuristico para cada PDB
	for (unsigned int i = 0; i < absts.size(); i++) {
		// obtener el estado
		abstract_state(absts[i], state, aux_state);

		// obtener el valor
		sum += *state_map_get(state_maps[i], aux_state);
	}
	return sum;
}