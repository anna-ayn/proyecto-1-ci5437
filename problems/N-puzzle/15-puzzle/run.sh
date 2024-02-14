make 15-puzzle/test1.pdb
make 15-puzzle/test2.pdb
make 15-puzzle/test3.pdb

echo "A* 15-puzzle (Manhattan)"
make 15-puzzle.astarM
./15-puzzle.astar < initialstates.txt

echo "IDA* 15-puzzle (Manhattan)"
make 15-puzzle.idastarM
./15-puzzle.astar < initialstates.txt

echo "A* 15-puzzle (PDBs aditivos)"
make 15-puzzle.astar
./15-puzzle.astar < initialstates.txt

echo "Ida* 15-puzzle (PDBs aditivos)"
make 15-puzzle.idastar
./15-puzzle.idastar < initialstates.txt
