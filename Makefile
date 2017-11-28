PLATFORM = linux64
INC      = /opt/gurobi602/linux64/include/
CPP      = g++
CARGS    = -m64 -g
CPPLIB   = -L /opt/gurobi602/linux64/lib/ -lgurobi_c++ -lgurobi60

all: gurobi_c++

run: run_c++

run_c++: run_gurobi_c++

gurobi_c++: gurobi.cpp
	$(CPP) $(CARGS) -o gurobi_teste gurobi.cpp -I $(INC) $(CPPLIB) -lm

run_gurobi_c++: gurobi_teste
	./gurobi_teste

clean:
	rm -rf *.o *_c *_c++ *.class *.log *.rlp *.lp *.bas *.ilp

