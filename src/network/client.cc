#include <client.hh>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

Client::Client (char* ip, int port) : Socket (port) {
	inet_pton (AF_INET, ip, &addr.sin_addr);
}

const socket_stream Client::connect (void) {
	if (::connect (sock, (sockaddr *)this, sizeof(sockaddr)) == -1)
  throw Exception ("Connect, Socket");

 return socket_stream (sock);
}
