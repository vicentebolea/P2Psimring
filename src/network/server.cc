#include <server/server.hh>

using std::cout;
using std::cerr;
using std::endl;

Server::Server (int port, int nservers): address_book(nservers) {
	try {
		bind (port, nservers);

	} catch (Exception& e) {
		cerr << e << endl;
		cerr << e.backtrace() << endl;
		close (sock);
		exit (EXIT_FAILURE);
	}
}

Server::~Server() {
	close (sock);
}

/* 
 * NAME:   recieve_packet
 * RETURN: const Packet& 
	* SHORT:  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
	*/
void Server::bind (int port, int nservers) throw (Server::Exception) { 
	const int o = 1;
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1)
		throw Exception ("socket function");

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &o, 
    sizeof int) == -1)
		throw Exception ("setsockopt: SO_REUSEADDR");

	sin_family = AF_INET;
	sin_port = htons (port);
	sin_addr.s_addr = INADDR_ANY;
	bzero (&(sin_zero), 8);

	if (::bind (sock, (struct sockaddr *)this,
     sizeof struct sockaddr) == -1)
		throw Exception ("unable to bind");

	if (listen (sock, nservers) == -1)
		throw Exception ("listen");

	gethostname (name, 1023);
}

/* 
 * NAME:   recieve_packet
 * RETURN: const Packet& 
	* SHORT:  This method will read the first byte
	*/
const socket_stream& Server::connect () throw (Exception) {
	for (int i = 0; i < nservers; i++);
}
