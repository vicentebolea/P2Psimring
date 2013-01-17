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

#include <exception.hh>
#include <socket_stream.hh>

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

	public:
		Server (int port, int nservers);
		~Server ();

		void	bind (int port, int nservers) throw (Exception);
		const socket_stream& connect () throw (Exception);
  
  void close();

		friend ostream& operator<< (ostream& in, const Server& s) {
			in << "[Server: "<< s.name << "]";
			in << " Sock: " << s.sock;
			in << " Address_book size: " << s.address_book_size;
			return in;
		}
};

#endif
