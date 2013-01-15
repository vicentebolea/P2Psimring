#include <server/server.hh>

using std::cout;
using std::cerr;
using std::endl;

Server::Server (int port, int nservers): address_book(nservers) {
	try {
		address_book = new Client_e [nservers];
		address_book_size = nservers;
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

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &o, sizeof int)==-1)
		throw Exception ("setsockopt: SO_REUSEADDR");

	sin_family = AF_INET;
	sin_port = htons (port);
	sin_addr.s_addr = INADDR_ANY;
	bzero (&(sin_zero), 8);

	if (::bind (sock, (struct sockaddr *)this, sizeof struct sockaddr)==-1)
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
void Server::connect () throw (Exception) {
	for (int i = 0; i < address_book_size; i++)
		address_book [i].connect(sock);
}

/** 
	* @brief  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
 * @return Packet ready 
	*/
bool Server::recieve (int fd, void* addr, size_t size) {
	size_t rec_b = 0;

	while (rec_b < size) {
		rec_b += recv (fd, ((uint8_t*)addr + rec_b),
    size - rec_b, MSG_WAITALL);

		if (rec_b	== (size_t)-1)
			return false;
 }
	return true;
}

/** 
	* @brief  This method will get the type of the
 *         incomming Packet. 
 * @return Packet.Type
	*/
Packet.Type Server::recieve_type (int fd) {
 Packet tmp;
 recv (fd, &tmp, sizeof Packet, MSG_BLOCK | MSG_PEEK);
 return tmp.getType();
}

/**
	* @brief  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
 * @return const Packet& 
	*/
const Packet& Server::recieve_packet (int fd) {
 static Packet tmp (QUIT);

	switch (recieve_type(fd)) {
		case QUERY:
			if (!recieve (fd, &tmp, sizeof(Query)))
				throw Exception ("Strange Packet Type");
			break;

		case STATS:
			if (!recieve (fd, &tmp, sizeof(Stat)))
				throw Exception ("Strange Packet Type");
			break;

		case UPDATE:
			if (!recieve (fd, &tmp, sizeof(Update)))
				throw Exception ("Strange Packet Type");
			break;

		case INFO: break;
		case QUIT: break;

		default:
			throw Exception ("Strange Packet Type");
	}
	return tmp;
}

/* 
	* @brief  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
 * @return bool 
	*/
bool Server::send_packet (int fd, const Packet& p) {
	try {
		switch (p.getType()) {
			case QUERY:
				if (send (fd, &p, sizeof(Query), 0) == -1)
					throw Exception ("problems with send");
				break;    

			case STATS:
				if (send (fd, &p, sizeof(Stat), 0) == -1)
					throw Exception ("problems with send");
				break;

				case UPDATE:
					if (send (fd, &p, sizeof(Update), 0) == -1)
						throw Exception ("problems with send");
				break;

			case INFO: break; 
			case QUIT: break;

			default:
				throw Exception ("Strange Packet Type");
		}
	} catch (Exception& e) {
		cerr << e << endl;		
		return false;
	}
	return true;
}
