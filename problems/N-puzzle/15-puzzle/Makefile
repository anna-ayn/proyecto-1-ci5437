# to make a PDB starting from foo.psvn  type the command:     make pdb ss=foo
# if $(absname).txt exists it will be used as the input (abstraction commands) to build the abstraction,
#   otherwise the user will enter the abstraction commands interactively.

CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=1 --bwd_history_len=0

psvn2c_core.c:
	@cp ../../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	@cp ../../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	@cp ../../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	@../../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	@rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.succ: %.c ../../../global/succ.c
	@$(CC) $(OPT) ../../../global/succ.c -include $< -o $@
	@rm -f $*.c

%.dist: %.c ../../../global/dist.cpp
	@$(CXX) $(OPT) ../../../global/dist.cpp -include $< -o $@
	@rm -f $*.c

%.distSummary: %.c ../../../global/distSummary.cpp
	@$(CXX) $(OPT) ../../../global/distSummary.cpp -include $< -o $@
	@rm -f $*.c

%.generator: %.c ../../../global/generator.cpp
	@$(CXX) $(OPT) ../../../global/generator.cpp -include $< -o $@
	@rm -f $*.c

abstractor:
	@$(CXX) $(OPT) ../../../src/abstractor.cpp ../../../src/psvn.cpp -o $@

%.pdb: abstractor
	@rm -f `dirname $*`_`basename $*`.{abst,pdb,psvn}
	@./abstractor `dirname $*`.psvn `dirname $*`_`basename $*` < `basename $*`.txt > /dev/null
	@make `dirname $*`_`basename $*`.distSummary
	@./`dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.pdb
	@rm -f abstractor `dirname $*`_`basename $*`.distSummary `dirname $*`_`basename $*`.psvn

%.astar: %.c ../../../global/astar.cpp 
	$(CXX) $(OPT) ../../../global/astar.cpp -include $< -include heuristic.cpp -o $@ || (rm -f *.c && false)
	@rm -f $*.c

%.idastar: %.c ../../../global/idastar.cpp 
	$(CXX) $(OPT) ../../../global/idastar.cpp -include $< -include heuristic.cpp -o $@

%.astarM: %.c ../../../global/astar.cpp
	$(CXX) $(OPT) ../../../global/astar.cpp -include $< -include manhattan.cpp -o $@

%.idastarM: %.c ../../../global/idastar.cpp
	$(CXX) $(OPT) ../../../global/idastar.cpp  -include $< -include manhattan.cpp -o $@
	
.PHONY: clean
clean:
	rm -fr *.c *.succ *.dist *.distSummary *.generator *.dist_pdb psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c abstractor *.dSYM *.o *~