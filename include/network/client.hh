#ifndef __CLIENT_H_
#define __CLIENT_H_

#include <socket.hh>
#include <socket_stream.hh>

namespace tcp_socket {
 class Client: public Socket {
  public:
   Client(char* ip, int port); 

   const socket_stream connect();
 };
}
#endif
