INCLUDE  := -I ./../../include
INCLUDE  += -I ./../../include/network

CXX      := g++
CXXFLAGS := -g -Wall $(INCLUDE)
AR       := ar
ARFLAGS  := -cvq 
#LDFLAGS  := -L ./../../lib -l UnitTest++

SOURCES := $(wildcard *.cc)
OBJECTS := $(patsubst %.cc, %.o, $(SOURCES))

%.o : %.cc 
	$(CXX) -c $(CXXFLAGS) $^ 

all: $(OBJECTS)
	$(AR) $(ARFLAGS) libtcp_sockets.a $^

clean:
	-rm *.o libtcp_sockets.a
