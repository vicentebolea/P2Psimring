INCLUDE := -I./../../include/lru/
INCLUDE += -I./../../lib

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE)
LDFLAGS := -L./../../lib -lUnitTest++

all:

hashtable: hashtable_test.cc
	$(CXX) -c $(CXXFLAGS) $^
	$(CXX) -o ./$@ hashtable_test.o $(LDFLAGS)

lru_map: lru_map_test.cc
	$(CXX) -c $(CXXFLAGS) $^
	$(CXX) -o ./$ lru_map_test.o $(LDFLAGS)

clean:						
	rm chain_test
