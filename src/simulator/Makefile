INCLUDE  := -I ./../../include
INCLUDE  += -I ./../../include/lru
INCLUDE  += -I ./../../include/network
INCLUDE  += -I ./../../include/simulator

CXX      := g++ -std=gnu++98
CXXFLAGS := -g -Wall  $(INCLUDE) -DDEBUG

SOURCES := node.cc query.cc #$(wildcard *.cc)
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: $(OBJECTS)

clean:
	-rm *.o
