#ifndef __SERVER_HH__
#define __SERVER_HH__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <exception.hh>
#include <packet/packet.hh>
#include <packet/query.hh>
#include <packet/stat.hh>
#include <packet/update.hh>
#include <server/client_e.hh>

using std::ostream;
using std::endl;

/*
 *
	*/
class Server: public sockaddr_in {
	public:
		class Exception: public ::Exception {
			public:
				Exception (const char* in) : ::Exception(__FILE__, in) {}
		};

	protected:
		char name [1024];
		int sock, address_book_size;
		Client_e* address_book;

		bool recieve (int fd, void* addr, size_t size);
		void	bind (int port, int nservers) throw (Exception);

	public:

		Server (int port, int nservers);
		~Server ();

		void	connect () throw (Exception);

		const Packet& recieve_packet (int fd);
		bool send_packet (int fd, const Packet& p);

		friend ostream& operator<< (ostream& in, const Server& s) {
			in << "[Server: "<< s.name << "]";
			in << " Sock: " << s.sock;
			in << " Address_book size: " << s.address_book_size;
			return in;
		}
};

#endif
