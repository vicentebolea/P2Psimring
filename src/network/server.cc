#include <server.hh>

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

namespace tcp_socket {

 Server::Server (int port) : Socket (port) {
  addr.sin_addr.s_addr = INADDR_ANY;
 }

 /**
  * @brief  This method will bind the socket to
  *         a given port and a multiples users
  *         Also will start to listen for incoming
  *         connections.
  */
 void 
  Server::bind (int nservers) throw (Exception) 
  { 
   if (::bind (sock, (sockaddr *)&addr,
      sizeof (sockaddr)) ==-1)
    throw Exception ("unable to bind");

   if (listen (sock, nservers) == -1)
    throw Exception ("listen");
  }

 /**
  * @brief  This method will read the first byte
  * @return const Packet& 
  */
 const socket_stream
  Server::connect (void) throw (Exception) 
  {
   struct sockaddr_in in;
   socklen_t len;

   len = sizeof (struct sockaddr_in);
   socket_stream aux (accept (sock, (struct sockaddr*)&in, &len));

   return aux;
  }
}
