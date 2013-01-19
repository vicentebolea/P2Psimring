#include <client.hh>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace tcp_socket {
	Client::Client (int port, const char* ip) : Socket (port) {
		inet_pton (AF_INET, ip, &addr.sin_addr);
	}

	const socket_stream 
	Client::connect (void) throw (Exception) {
		if (::connect (sock, (sockaddr *)&addr, sizeof(sockaddr))
			!= 0)
			throw Exception ("Connect, Socket");

		return socket_stream (sock);
	}
}
