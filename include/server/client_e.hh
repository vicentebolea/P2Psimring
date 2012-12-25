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
	private:
		int fd;

	public:
		class Exception: public ::Exception {
			public:
				Exception(const char* in) : ::Exception(in) {
					char tmp [100], hostn[100];

					gethostname (hostn, 100);
					snprintf (tmp, 100,
							"NETWORKING:CLIENT_E [ERRNO: %i] [STR: %s]"
							"[REASON: %s] [HOSTNAME: %s]",
							errno, strerror(errno), in, hostn);
					strncat (message, tmp, 100);
				}
		};
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

		bool connect (int sock) throw (NetException) { 
			socklen_t ss = sizeof (struct sockaddr_in); 	

			fd = accept (sock, (struct sockaddr*)this, &ss);
			if (fd == -1)
				throw Exception ("Connect");

			return true;
		}

		void close (int sock) {
			::close (sock);
		}

		//	const string& toString () {
		//		char tmp [64];	
		//		sprintf (tmp, "FD: %i IP: %s", fd, inet_ntoa (addr.sin_addr));
		//		return string (tmp);
		//	}

		friend ostream& operator<< (ostream& in, Client_e& c) {
			in << "FD: " << c.fd << " IP: ";
			in << inet_ntoa (c.sin_addr) << std::endl;
			return in;
		}
};

#endif
