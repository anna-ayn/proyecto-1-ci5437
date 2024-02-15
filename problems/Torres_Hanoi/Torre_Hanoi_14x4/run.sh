make hanoi_14x4/group_1.pdb
make hanoi_14x4/group_2.pdb

echo "A* hanoi_14x4 (max PDBs)"
make hanoi_14x4.astar
./hanoi_14x4.astar < initialstates.txt

echo "IDA* hanoi_14x4 (max PDBs)"
make hanoi_14x4.idastar
./hanoi_14x4.idastar < initialstates.txt