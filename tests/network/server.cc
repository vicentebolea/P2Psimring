#include <server.hh>
#include <iostream>

using namespace std;
using namespace tcp_socket;

int main (){ 
 Server s (9998); 
 s.setUp();
 s.bind();
	socket_stream ss = s.connect();
	const char* m = ss.recieve<char[32]>();
	cout << m << endl;
 s.close();

 return 0;
}
