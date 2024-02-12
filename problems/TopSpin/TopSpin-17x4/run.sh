make topspin17x4/group_1.pdb
make topspin17x4/group_2.pdb

echo "A* topspin17x4 (max PDBs)"
make topspin17x4.astar
./topspin17x4.astar < initialstates.txt

echo "IDA* topspin17x4 (max PDBs)"
make topspin17x4.idastar
./topspin17x4.idastar < initialstates.txt