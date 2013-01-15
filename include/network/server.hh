/**
 *
	*/
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
#include <vector>

#include <exception.hh>
#include <packet.hh>
#include <query.hh>
#include <stat.hh>
#include <update.hh>
#include <client_e.hh>

using std::vector;
using std::ostream;
using std::endl;

class Server: public sockaddr_in {
	public:
		class Exception: public ::Exception {
			public:
				Exception (const char* in) : ::Exception(__FILE__, in) {}
		};

	protected:
		char name [1024];
		int sock;
  vector<address_page> address_book;

  Packet.Type recieve_type (int fd);
		bool recieve (int fd, void* addr, size_t size);
		void	bind (int port, int nservers) throw (Exception);

	public:

		Server (int port, int nservers);
		~Server ();

		void	connect () throw (Exception);

  Packet.Type getType() const;
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
