/**
 * @namespace  tcp_socket
 * @class      Server
 * @brief      Class which wrap server socket BSD
 *********************************************************			
 *
 */
#ifndef __SERVER_HH__
#define __SERVER_HH__

#include <socket.hh>
#include <socket_stream.hh>

namespace tcp_socket {
 class Server: public Socket {
  public:
   Server (int port);

   void	bind (int nservers = 1024) throw (Exception);
   const socket_stream connect (void) throw (Exception);
 };
}

#endif
