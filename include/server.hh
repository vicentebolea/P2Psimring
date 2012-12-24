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

#include <client_e.hh>
#include <exception.hh>

using namespace std;

class Server: public sockaddr_in {
	private:
		char name [1024];
		int sock;
		Client_e node [NSERVERS];

		bool Recieve (int fd, void* addr, size_t size);

	public:
		Server (int port, int nservers);
		~Server ();

		void	Bind (int port, int nservers) throw (NETException);
		void	connect () throw (NETException);
		void	reconnect () throw (NETException);

		const Packet& recieve_packet (int fd);
		bool send_packet (const Packet& p);
};

#endif
