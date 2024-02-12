make topspin14x4/group_1.pdb
make topspin14x4/group_2.pdb

echo "A* topspin14x4 (max PDBs)"
make topspin14x4.astar
./topspin14x4.astar < initialstates.txt

echo "IDA* topspin14x4 (max PDBs)"
make topspin14x4.idastar
./topspin14x4.idastar < initialstates.txt