#include <client.hh>
#include <iostream>
#include <string.h>

using namespace std;
using namespace tcp_socket;

int main (){ 
 Client c (9998, "127.0.0.1"); 
 c.setUp();
	socket_stream ss =  c.connect();
	char msg[32];
	strcpy (msg, "hey guys");
	ss.send<char[32], 1> (msg);
 c.close();

 return 0;
}
