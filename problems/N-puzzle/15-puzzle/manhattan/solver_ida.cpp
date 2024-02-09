#include "../../utils/pdb.hpp"
#include "../../algorithms/IDA.hpp"
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <cmath>

using namespace std;

struct PDB_M : PDB {
    int h(state_t current_state) {
        int score = 0;
        for (size_t i = 0; i < NUMVARS; i++) {
            int value = current_state.vars[i];
            int displacement = value - i;
            score += pow(displacement / NUMVARS, 2) + pow(displacement % NUMVARS, 2);
        }
        return score;
    }
};

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    // Inicializar
    vector<string> names{"abst_1", "abst_2", "abst_3"};
    PDB_M pdb;
    state_t state;
 
    // Leer input
    read_state(argv[1], &state);

    // Ejecutar IDA*
    optional<state_t> result = do_ida(state, pdb);

    // Salida
    cout << "Solution found: " << result.has_value() << endl;

    return 0;
}