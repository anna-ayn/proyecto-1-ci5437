make 24-puzzle/test1.pdb
make 24-puzzle/test2.pdb
make 24-puzzle/test3.pdb
make 24-puzzle/test4.pdb
make 24-puzzle/test5.pdb
make 24-puzzle/test6.pdb

make 24-puzzle.astar
echo "A* 24-puzzle (PDBs aditivos)"
./24-puzzle.astar < ../../../benchmarks/24-puzzle/24_puzzle_50_instances_korf.txt

make 24-puzzle.idastar
echo "IDA* 24-puzzle (PDBs aditivos)"
./24-puzzle.idastar < ../../../benchmarks/24-puzzle/24_puzzle_50_instances_korf.txt
