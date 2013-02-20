INCLUDE  := -I ./../../include
INCLUDE  += -I ./../../include/network
INCLUDE  += -I ./../../lib

CXX      := g++
CXXFLAGS := -g -Wall $(INCLUDE)
LDFLAGS  := -L ./../../lib -l UnitTest++
EXE      := server client packet socket_stream

all: depend $(EXE) 

packet: packet.cc
	$(CXX) -o ./$@ $(CXXFLAGS) $^ $(LDFLAGS)

socket_stream: socket_stream.cc
	$(CXX) -o ./$@ $(CXXFLAGS) $^      \
	../../src/network/socket_stream.cc \
	$(LDFLAGS)

server: server.cc
	$(CXX) -o ./$@ $(CXXFLAGS) $^      \
	../../src/network/server.cc        \
	../../src/network/socket_stream.cc \
	../../src/network/socket.cc

client: client.cc
	$(CXX) -o ./$@ $(CXXFLAGS) $^      \
	../../src/network/client.cc        \
	../../src/network/socket_stream.cc \
	../../src/network/socket.cc

depend:
	@if ! [ -a ./../../lib/libUnitTest++.a ] || ! [ -a ./../../lib/minIni.o ]; then \
		make -C ./../../lib;                                               \
	fi;

clean:
	-rm *.o $(EXE)
