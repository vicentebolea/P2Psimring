#include <server.hh>
#include <iostream>

using namespace tcp_socket;

int main (){ 
 Server s (9999); 
 s.setUp();
 s.bind();
 s.close();

 return 0;
}
