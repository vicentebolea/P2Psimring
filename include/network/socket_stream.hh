/**
 *
 */

#ifndef __SOCKET_STREAM_HH_
#define __SOCKET_STREAM_HH_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <exception.hh>
#include <packet.hh>

class socket_stream {
 protected:
  int sock;

 public:
  socket_stream (int);
  ~socket_stream ();

  void setBlocking (bool);
  uint8_t getType() const;
  void close (void);

  template <class msg> const msg& recieve (void);
  template <class msg, int type> bool send (const msg&);
};

/** 
	* @brief  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
 * @return Packet ready 
	*/
template <class msg>
const msg& socket_stream::recieve (void) {
 static Packet<msg> packet (0, 0);
 int ret = recv (sock, &packet, sizeof packet, MSG_WAITALL);
 if (ret < 0)
  perror ("HERE");

 return packet.getMessage();
}

/** 
	* @brief  This method will read the first byte
	*         of the packet and depend of the type it will
	*         create a diferent object.
 * @return Packet ready 
	*/
template <class msg, int type>
bool socket_stream::send (const msg& m) {
 Packet<msg> packet (type, m);

 int ret = ::send (sock, &packet, sizeof packet, MSG_WAITALL);
 if (ret == -1) {
  switch (errno) {
   case EAGAIN: break;
   default: throw Exception ("send message");
  }
  return false;
 }
 return true;
}

#endif
