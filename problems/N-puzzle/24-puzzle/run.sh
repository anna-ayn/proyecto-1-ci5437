make 24-puzzle/test1.pdb
make 24-puzzle/test2.pdb
make 24-puzzle/test3.pdb
make 24-puzzle/test4.pdb
make 24-puzzle/test5.pdb
make 24-puzzle/test6.pdb

echo "A* 24-puzzle (PDBs aditivos)"
make 24-puzzle.astar
./24-puzzle.astar < initialstates.txt

echo "IDA* 24-puzzle (PDBs aditivos)"
make 24-puzzle.idastar
./24-puzzle.idastar < initialstates.txt