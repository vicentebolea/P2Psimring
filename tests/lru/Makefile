INCLUDE := -I./../../include/lru/
INCLUDE += -I./../../lib

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE) -std=gnu++98 #-Wno-non-virtual-dtor
LDFLAGS := -L./../../lib -lUnitTest++

SOURCES := hashtable.cc lru_map.cc main.cc
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: $(OBJECTS)
	$(CXX) -o ./lru_test $^ $(LDFLAGS)

clean:						
	-rm *.o lru_test
