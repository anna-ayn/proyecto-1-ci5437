make rubik3Sticker/corner_1.pdb
make rubik3Sticker/corner_2.pdb
make rubik3Sticker/corner_3.pdb
make rubik3Sticker/corner_4.pdb
make rubik3Sticker/corner_5.pdb
make rubik3Sticker/edge_1.pdb
make rubik3Sticker/edge_2.pdb

echo "IDA* rubik3Sticker (max PDBs)"
make rubik3Sticker.idastar
./rubik3Sticker.idastar < initialstates3.txt
