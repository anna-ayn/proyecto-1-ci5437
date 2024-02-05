CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --no_abstraction --backwards_moves --history_len=0

psvn2c_core.c:
	cp ../../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	../../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.bfs1: %.c ../../../global/bfs1.cpp
	$(CXX) $(OPT) ../../../global/bfs1.cpp -include $< -o $@
	rm -f $*.c

%.bfs2: %.c ../../../global/bfs2.cpp
	$(CXX) $(OPT) ../../../global/bfs2.cpp -include $< -o $@
	rm -f $*.c

%.iddfs1: %.c ../../../global/iddfs1.cpp
	$(CXX) $(OPT) ../../../global/iddfs1.cpp -include $< -o $@
	rm -f $*.c	

%.iddfs2: %.c ../../../global/iddfs2.cpp
	$(CXX) $(OPT) ../../../global/iddfs2.cpp -include $< -o $@
	rm -f $*.c	

%.succ: %.c ../../../global/succ.c
	$(CC) $(OPT) ../../../global/succ.c -include $< -o $@
	rm -f $*.c

%.dist: %.c ../../../global/dist.cpp
	$(CXX) $(OPT) ../../../global/dist.cpp -include $< -o $@
	rm -f $*.c

%.distSummary: %.c ../../../global/distSummary.cpp
	$(CXX) $(OPT) ../../../global/distSummary.cpp -include $< -o $@
	rm -f $*.c

.PHONY: clean
clean:
	rm -fr *.succ *.dist *.distSummary psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c *.dSYM *.o *~
