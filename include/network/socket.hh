/**
 * @namespace  tcp_socket
 * @class      Socket
 * @brief      Class which wrap BSD sockets, should be seen
 *             as an interface
 *********************************************************			
 *
 */
#ifndef __SOCKET_HH_
#define __SOCKET_HH_

#include <iostream>
#include <string>
#include <string.h>
#include <exception.hh>
#include <socket_stream.hh>

using std::string;

namespace tcp_socket {

 class Socket {
  public:
   class Exception: public ::Exception {
    public:
     Exception (const char* in) : ::Exception(__FILE__, in) {}
   };

  protected:
   sockaddr_in addr;
   char name [1024];
   int sock;

  public:
   Socket (int);
   Socket (const Socket& that) { 
    this->sock = that.sock;
    memcpy (&this->addr, &that.addr, sizeof (struct sockaddr_in));
   }
   const Socket& operator= (const Socket& that) {
    this->sock = that.sock;
    memcpy (&this->addr, &that.addr, sizeof (struct sockaddr_in));
    return *this;
   }
   virtual ~Socket ();

   virtual const socket_stream connect (void) = 0;

   void setUp (void) throw (Exception);
   void close (void);

   const string& toString (void);
 };
}
#endif 
