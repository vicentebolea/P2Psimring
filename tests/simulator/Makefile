INCLUDE := -I ./../../lib
INCLUDE += -I ./../../include
INCLUDE += -I ./../../include/simulator
INCLUDE += -I ./../../include/network
INCLUDE += -I ./../../include/lru

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE) -std=gnu++98 
LDFLAGS := -L ./../../lib -L ./../../src/simulator 
LDFLAGS += -l UnitTest++ -l pthread

SOURCES := node.cc
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: depend $(OBJECTS)
	$(CXX) -o ./lru_test $(OBJECTS) $(LDFLAGS)

depend:
	@if ! [ -a ./../../lib/libUnitTest++.a ] || ! [ -a ./../../lib/minIni.o ]; then \
		make -C ./../../lib;                                               \
	fi;
	
	@if ! [ -a ./../../src/simulator/node.o ]; then     \
 		g++ -c $(CXXFLAGS) ./../../src/simulator/node.cc; \
	fi;

clean:						
	-rm *.o lru_test
