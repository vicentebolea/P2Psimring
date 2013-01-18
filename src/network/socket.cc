#include <socket.hh>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace tcp_socket {

 Socket::Socket (int port) {
  addr.sin_family = AF_INET;     
  addr.sin_port = htons (port);   
  bzero (&addr.sin_zero, 8); 
  gethostname (name, 1023);
 }

 Socket::~Socket() {
  close ();
 }

 void Socket::setUp (void) throw (Exception) {
  int o = 1;

  sock = ::socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == -1)
   throw Exception ("socket function");

  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &o, 
     sizeof (int)) == -1)
   throw Exception ("setsockopt: SO_REUSEADDR");
 }

 void Socket::close (void) {
  ::close (sock);
 }

 const string& Socket::toString (void) {
  static string tmp = "[Server: ";
  tmp += name;
  tmp += " Sock: ";
  tmp += sock;
  return tmp;
 }
}
