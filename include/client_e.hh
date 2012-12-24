#ifndef _CLIENT_E_HH_
#define _CLIENT_E_HH_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include <exception.hh>

using std::string;
using std::ostream;

struct Client_e {

	struct sockaddr_in addr;
	int fd;

	Client_e () {}
	~Client_e () {}

	Client_e (const Client_e& e) {
		addr = e.addr;
		fd = e.fd;
	}

	const Client_e& operator= (const Client_e& e) {
		addr = e.addr;
		fd = e.fd;
		return *this;
	}
	
	bool connect (int sock) throw (NetException) { 
		socklen_t ss = sizeof (struct sockaddr_in); 	
		if ((fd = accept (sock, (struct sockaddr*)&addr, &ss)) == -1)
			throw NetException (string("Connect") + toString());
	}

	const string& toString () {
		char tmp [64];	
		sprintf (tmp, "FD: %i IP: %s", fd, inet_ntoa (addr));
		return string (tmp);
	}

	friend ostream& operator<< (ostream& in, Client_e& c) {
		in << "FD: " << c.fd << " IP: ";
		in << inet_ntoa (c.addr) << std::endl;
		return in;
	}
};

#endif
