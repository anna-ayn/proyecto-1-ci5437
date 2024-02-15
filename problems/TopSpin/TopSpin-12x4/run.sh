make topspin12x4/group_1.pdb
make topspin12x4/group_2.pdb

echo "A* topspin12x4 (max PDBs)"
make topspin12x4.astar
./topspin12x4.astar < initialstates.txt

echo "IDA* topspin12x4 (max PDBs)"
make topspin12x4.idastar
./topspin12x4.idastar < initialstates.txt