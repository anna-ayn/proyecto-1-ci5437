#include <vector>
#include <string>
using namespace std;

// HEURISTIC PARA 15-PUZZLE

// Vectores que guardan los PDBs y abstracciones
vector<abstraction_t*> absts;
vector<state_map_t*> pdbs;

/*
    Funcion que abre los PDBs y los almacena en el vector
*/
void open_pdbs() {
    // tenemos 3 PDBs
	vector<string> filepdbs = {"rubik3Sticker_corner_1.pdb", "rubik3Sticker_corner_2.pdb", "rubik3Sticker_corner_3.pdb", "rubik3Sticker_corner_4.pdb", "rubik3Sticker_corner_5.pdb", "rubik3Sticker_edge_1.pdb", "rubik3Sticker_edge_2.pdb"};
    vector<string> fileabsts = {"rubik3Sticker_corner_1.abst", "rubik3Sticker_corner_2.abst", "rubik3Sticker_corner_3.abst", "rubik3Sticker_corner_4.abst", "rubik3Sticker_corner_5.abst", "rubik3Sticker_edge_1.abst", "rubik3Sticker_edge_2.abst"};

    // itero en cada archivo PDB
	for (unsigned int i = 0; i < filepdbs.size(); i++) {
        // abro el archivo
		FILE *filepdb = fopen(filepdbs[i].c_str(), "r");
        // verifico que no este vacio el archivo
		assert(filepdb != NULL);
        // guardo el PDB y la abstraccion en los vectores, y cierro el archivo
		pdbs.push_back(read_state_map(filepdb));
		absts.push_back(read_abstraction_from_file(fileabsts[i].c_str()));
		fclose(filepdb);
	}
}


/*
    Funcion que calcula el valor heuristico de un estado 
    Recibe:
        - state: el estado al que se le calculara el valor heuristico
    Retorna:
        Retorna el valor heuristico del estado
*/
int heuristic(state_t *state) {
    long long int h_value = 0;
	state_t *temp_state = new state_t;

	// calcular el valor heuristico para cada PDB
	for (unsigned int i = 0; i < pdbs.size(); i++) {
		// obtener el estado
		abstract_state(absts[i], state, temp_state);
		// obtener y actualizar el valor heuristico
		long long int temp = *state_map_get(pdbs[i], temp_state);
		h_value = max(h_value, temp);
	}
	// liberar memoria
	delete temp_state;
	return h_value;
}
