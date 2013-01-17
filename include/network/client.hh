#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <socket_stream.hh>

struct Client: public sockaddr_in {
	struct hostent* host;	
	int sock;

	Client(char* ip, int port); 
	~Client();

	const socket_stream& connect();
};

#endif
