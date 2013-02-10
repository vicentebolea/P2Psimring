#include <client.hh>
#include <iostream>
#include <string.h>

using namespace std;
using namespace tcp_socket;

struct message {
	char msg[32];

	message () {}
	message (const char *m) {
		strcpy (msg, m);
	}
	message (const message& m) {
		strcpy (msg, m.msg);
	}
};

int main (){ 
 Client c (9998, "127.0.0.1"); 
 c.setUp();
	socket_stream ss =  c.connect();
	ss.send<int, 1> (0x00ff);
	//ss.send<message, 1> (message ("Hey guys"));
	message m2 = ss.recieve<message>(); 
	cout << m2.msg << endl;
 c.close();

 return 0;
}
