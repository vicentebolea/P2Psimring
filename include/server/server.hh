#ifndef __SERVER_H__
#define __SERVER_H__

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

class Server: public sockaddr_in {
	private:
		char name [1024];
		int sock, address_book_size;
		Client_e* address_book;

		bool recieve (int fd, void* addr, size_t size);
		void	bind (int port, int nservers) throw (Exception);

	public:
		class Exception: public ::Exception {
			public:
				Exception (const char* in) : ::Exception(__FILE__, in) {}
		};

		Server (int port, int nservers);
		~Server ();

		void	connect () throw (Exception);

		const Packet& recieve_packet (int fd);
		bool send_packet (const Packet& p);
};

#endif
