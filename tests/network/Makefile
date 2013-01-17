INCLUDE := -I./../../include
INCLUDE += -I./../../include/network
INCLUDE += -I./../../lib

CXX := g++
CXXFLAGS := -g -Wall $(INCLUDE)
LDFLAGS := -L./../../lib -lUnitTest++

all: packet

packet: packet.cc
	$(CXX) -c $(CXXFLAGS) $^
	$(CXX) -o ./$@ packet.o $(LDFLAGS)

socket_stream: socket_stream_test.cc
	$(CXX) -c $(CXXFLAGS) $^ ../../src/network/socket_stream.cc
	$(CXX) -o ./$@ socket_stream.o socket_stream_test.o $(LDFLAGS)

clean:
	-rm *.o packet socket_stream
