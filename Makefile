# Copyright 2014, Gurobi Optimization, Inc.

PLATFORM = linux64
INC      = ../../include/
CPP      = g++
CARGS    = -m64 -g
CPPLIB   = -L../../lib/ -lgurobi_c++ -lgurobi60

all: diet_c++

run: run_c++

run_c++: run_diet_c++

diet_c++: ../c++/diet_c++.cpp
	$(CPP) $(CARGS) -o diet_c++ ../c++/diet_c++.cpp -I$(INC) $(CPPLIB) -lpthread -lm

run_diet_c++: diet_c++
	./diet_c++

clean:
	rm -rf *.o *_c *_c++ *.class *.log *.rlp *.lp *.bas *.ilp

