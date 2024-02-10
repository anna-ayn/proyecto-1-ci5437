make 15-puzzle/test1.pdb
make 15-puzzle/test2.pdb
make 15-puzzle/test3.pdb

echo "idastar 15-puzzle"
make 15-puzzle.idastar
./15-puzzle.idastar < initialstates.txt

echo "A* 15-puzzle (Manhattan Distance)"
make 15-puzzle.astarM
./15-puzzle.astar < initialstates.txt