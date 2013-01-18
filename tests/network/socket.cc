#include <socket.hh>
#include <iostream>

using namespace tcp_socket;

int main (){ 
 Socket s (9999); 
 s.setUp();
 s.close();

 return 0;
}
