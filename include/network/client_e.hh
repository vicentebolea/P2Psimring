#ifndef _CLIENT_E_HH_
#define _CLIENT_E_HH_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>
#include <iostream>
#include <string>

#include <exception.hh>

using std::string;
using std::ostream;

class Client_e: public sockaddr_in {
	public:
		class Exception: public ::Exception {
			public:
				Exception (const char* in) : ::Exception (__FILE__, in) {}
		};

	protected:
		int fd;

	public:
		Client_e () {}
		~Client_e () {}

		Client_e (const Client_e& e) {
			(sockaddr_in)*this = (sockaddr_in)e;
			fd = e.fd;
		}

		const Client_e& operator= (const Client_e& e) {
			(sockaddr_in)*this = (sockaddr_in)e;
			fd = e.fd;
			return *this;
		}

		bool connect (int sock) throw (Exception) { 
			socklen_t ss = sizeof (struct sockaddr_in); 	

			fd = accept (sock, (struct sockaddr*)this, &ss);
			if (fd == -1)
				throw Exception ("Connect");

			return true;
		}

		void close (int sock) {
			::close (sock);
		}

		friend ostream& operator<< (ostream& in, const Client_e& c) {
			in << "[Client_e] FD: " << c.fd << " IP: ";
			in << inet_ntoa (c.sin_addr);
			return in;
		}
};

#endif
