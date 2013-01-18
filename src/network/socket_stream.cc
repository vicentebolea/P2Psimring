#include <socket_stream.hh>

namespace tcp_socket {

 socket_stream::socket_stream (int fd): sock(fd) {}
 socket_stream::~socket_stream () {
  (void)close ();
 }

 void socket_stream::setBlocking (bool flag) {
  if (flag) {
   fcntl (sock, F_SETFL, O_SYNC);
  } else {
   fcntl (sock, F_SETFL, O_NONBLOCK);
  }
 }

 /** 
  * @brief  This method will get the type of the
  *         incomming Packet. 
  * @return Packet.Type
  */
 uint8_t socket_stream::getType (void) const {
  uint8_t tmp;
  recv (sock, &tmp, 1, MSG_PEEK);
  return tmp;
 }

 void socket_stream::close () {
  ::close (sock);
 }
}
