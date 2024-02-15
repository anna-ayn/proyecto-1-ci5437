make hanoi_18x4/group_1.pdb
make hanoi_18x4/group_2.pdb

echo "A* hanoi_18x4 (max PDBs)"
make hanoi_18x4.astar
./hanoi_18x4.astar < initialstates.txt

echo "IDA* hanoi_18x4 (max PDBs)"
make hanoi_18x4.idastar
./hanoi_18x4.idastar < initialstates.txt