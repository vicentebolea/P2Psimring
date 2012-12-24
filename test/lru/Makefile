INCLUDE := ./../../include/lru/

CXX := g++
CXXFLAGS := -g -Wall -I$(INCLUDE)

chain_test: chain_test.cc
	$(CXX) $(CXXFLAGS) -o ./$@ $^

clean:						
	rm chain_test
