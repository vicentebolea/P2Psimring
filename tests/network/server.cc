#include <server.hh>
#include <iostream>

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
 Server s (9998); 
 s.setUp();
 s.bind();
	socket_stream ss = s.connect();
	const message m1 = ss.recieve<message>();
	cout << m1.msg << endl;
	ss.send<message, 1> (message("Hey man"));
 s.close();

 return 0;
}
