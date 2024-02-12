make hanoi_12x4/group_1.pdb
make hanoi_12x4/group_2.pdb

echo "A* hanoi_12x4 (max PDBs)"
make hanoi_12x4.astar
./hanoi_12x4.astar < initialstates.txt

echo "IDA* hanoi_12x4 (max PDBs)"
make hanoi_12x4.idastar
./hanoi_12x4.idastar < initialstates.txt