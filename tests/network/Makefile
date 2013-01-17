INCLUDE := -I./../../include/network
INCLUDE += -I./../../lib

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE)
LDFLAGS := -L./../../lib -lUnitTest++

all: packet

packet: packet.cc
	$(CXX) -c $(CXXFLAGS) $^
	$(CXX) -o ./$@ packet.o $(LDFLAGS)

#lru_map: lru_map_test.cc
#$(CXX) -c $(CXXFLAGS) $^
#$(CXX) -o ./$@ lru_map_test.o $(LDFLAGS)

clean:						
	rm *.o packet 
