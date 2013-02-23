INCLUDE  := -I ./../../include
INCLUDE  += -I ./../../include/lru
INCLUDE  += -I ./../../include/network
INCLUDE  += -I ./../../include/simulator

CXX      := g++
CXXFLAGS := -g -Wall $(INCLUDE) -std=gnu++98
LDFLAGS  := -l pthread

SOURCES := node.cc query.cc #$(wildcard *.cc)
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: $(OBJECTS)

clean:
	-rm *.o
