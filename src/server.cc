#include <server/server.hh>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

Server::Server (int port, int nservers) {
	try {
		bind (port, nservers);

	} catch (NetException& e) {
		cerr << e << endl;
		cerr << e.backTrace() << endl;
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
void Server::bind (int port, int nservers) throw (NetException) { 
	const int o = 1;
	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1)
		throw NetException ("socket function");

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &o, sizeof(int))==-1)
		throw NetException ("setsockopt: SO_REUSEADDR");

	sin_family = AF_INET;
	sin_port = htons (port);
	sin_addr.s_addr = INADDR_ANY;
	bzero (&(sin_zero), 8);

	if (::bind(sock, (struct sockaddr *)this, sizeof(struct sockaddr))==-1)
		throw NetException ("unable to bind");

	if (listen (sock, nservers) == -1)
		throw NetException ("listen");

	gethostname (name, 1023);
}

/* 
 * NAME:   recieve_packet
 * RETURN: const Packet& 
	* SHORT:  This method will read the first byte
	*/
void Server::connect () throw (NetException) {
	for (int i = 0; i < NSERVERS; i++)
		node[i].connect();
}

/* 
 * NAME:   recieve_packet
 * RETURN: const Packet& 
	* SHORT:  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
	*/
bool Server::recieve (int fd, void* addr, size_t size) {
	size_t rec_b = 0;

	while (rec_b < size)
		rec_b += recv (fd, addr + rec_b, size - rec_b, MSG_WAITALL);
		if (rec_b	== -1)
			return false;

	return true;
}

/* 
 * NAME:   recieve_packet
 * RETURN: const Packet& 
	* SHORT:  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
	*/
const Packet& Server::recieve_packet (int fd) {
	Packet tmp;
	Recieve (fd, (Packet)&tmp, sizeof(Packet));

	switch (tmp.type) {
		case query:
			if (!recieve (fd, (Query)&tmp, sizeof(Query)-sizeof(Packet)))
				throw NetException ("Strange Packet Type");
			break;

		case stat:
			if (!recieve (fd, (Stat)&tmp, sizeof(Stat)-sizeof(Packet)))
				throw NetException ("Strange Packet Type");
			break;

		case update:
			if (!recieve (fd, (Update)&tmp, sizeof(Update)-sizeof(Packet)))
				throw NetException ("Strange Packet Type");
			break;

		case info: break;
		case quit: break;

		default:
			throw NetException ("Strange Packet Type");
	}
	return tmp;
}

/* 
 * NAME:   send_packet
 * RETURN: bool 
	* SHORT:  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
	*/
bool Server::send_packet (const Packet& p) {
	try {
		switch (tmp.packet) {
			case query:
				if (send (fd, &p, sizeof(Query), 0) == -1)
					throw NetException ("problems with send");
				break;    

			case stat:
				if (send (fd, &p, sizeof(Stats), 0) == -1)
					throw NetException ("problems with send");
				break;

				case update:
					if (send (fd, &p, sizeof(Update), 0) == -1)
						throw NetException ("problems with send");
				break;

			case info: break; 
			case quit: break;

			default:
				throw NetException ("Strange Packet Type");
		}
	} catch (NetException& e) {
		cerr << e << endl;		
		return false;
	}
	return true;
}
