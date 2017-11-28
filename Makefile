# Copyright 2014, Gurobi Optimization, Inc.

PLATFORM = linux64
INC      = ../../include/
CPP      = g++
CARGS    = -m64 -g
CPPLIB   = -L../../lib/ -lgurobi_c++ -lgurobi60

all: gurobi_c++

run: run_c++

run_c++: run_gurobi_c++

gurobi_c++: gurobi.cpp
	$(CPP) $(CARGS) -o gurobi_teste gurobi.cpp -I$(INC) $(CPPLIB) -lpthread -lm

run_gurobi_c++: gurobi_teste
	./gurobi_teste

clean:
	rm -rf *.o *_c *_c++ *.class *.log *.rlp *.lp *.bas *.ilp

