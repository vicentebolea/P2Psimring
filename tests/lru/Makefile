INCLUDE := -I ./../../include/lru/
INCLUDE += -I ./../../lib

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE) -std=gnu++98 #-Wno-non-virtual-dtor
LDFLAGS := -L ./../../lib -lUnitTest++

SOURCES := hashtable.cc lru_map.cc main.cc
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: $(OBJECTS) depend
	$(CXX) -o ./lru_test $(OBJECTS) $(LDFLAGS)

depend:
	@if ! [ -a ./../../lib/libUnitTest++.a ] || ! [ -a ./../../lib/minIni.o ]; then \
		make -C ./../../lib;                                               \
	fi;

clean:						
	-rm *.o lru_test
