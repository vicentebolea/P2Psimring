INCLUDE := -I ./../../lib
INCLUDE += -I ./../../include
INCLUDE += -I ./../../include/simulator
INCLUDE += -I ./../../include/network
INCLUDE += -I ./../../include/lru

CXX := g++ -std=gnu++98
CXXFLAGS := -g -Wall $(INCLUDE)  
LDFLAGS := -L ./../../lib -L ./../../src/network 
LDFLAGS += -l UnitTest++ -l pthread -l tcp_sockets 

SOURCES := node.cc main.cc
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: clean depend $(OBJECTS) node_test

node_test:
	$(CXX) -o ./node_test $(OBJECTS) \
           ./../../src/simulator/node.o      \
           ./../../src/simulator/query.o     \
           $(LDFLAGS)

depend:
	@if ! [ -a ./../../lib/libUnitTest++.a ] || ! [ -a ./../../lib/minIni.o ]; then \
		make -C ./../../lib;                                               \
	fi;
	
	@if ! [ -a ./../../src/simulator/node.o ] || ! [ -a ./../../src/simulator/query.o ]; then     \
 	make -C ./../../src/simulator; \
	fi;

clean:						
	-rm *.o node_test
	make -C ./../../src/simulator clean
