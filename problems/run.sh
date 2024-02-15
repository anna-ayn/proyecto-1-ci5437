#!/bin/bash

run_script_and_save_results() {
    local script="$1"
    local script_directory="$(dirname "$script")"
    local results_file="$script_directory/run_results.txt"
    echo "Ejecutando $script y guardando resultados en $results_file"
    (cd "$script_directory" && ./$(basename "$script")) > "$results_file" 2>&1
    echo "Resultados guardados en $results_file"
}

# RubiksCube
run_script_and_save_results "RubiksCube/RubikCube/run.sh"

# TopSpin
run_script_and_save_results "TopSpin/TopSpin-12x4/run.sh"
run_script_and_save_results "TopSpin/TopSpin-14x4/run.sh"
run_script_and_save_results "TopSpin/TopSpin-17x4/run.sh"

# Torres de Hanoi
run_script_and_save_results "Torres_Hanoi/Torre_Hanoi_12x4/run.sh"
run_script_and_save_results "Torres_Hanoi/Torre_Hanoi_14x4/run.sh"
run_script_and_save_results "Torres_Hanoi/Torre_Hanoi_18x4/run.sh"

# 15-puzzle
run_script_and_save_results "N-puzzle/15-puzzle/run.sh"
