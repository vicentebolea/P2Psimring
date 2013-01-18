/**
 *
 */
#ifndef __SOCKET_HH_
#define __SOCKET_HH_

#include <iostream>
#include <string>
#include <exception.hh>
#include <socket_stream.hh>

using std::ostream;
using std::string;

namespace tcp_socket {

 class Socket {
  public:
   class Exception: public ::Exception {
    public:
     Exception (const char* in) : ::Exception(__FILE__, in) {}
   };

  protected:
   struct sockaddr_in addr;
   char name [1024];
   int sock;

  public:
   Socket (int);
   ~Socket ();

   virtual const socket_stream connect (void) = 0;

   void setUp (void) throw (Exception);
   void close (void);

   const string& toString (void);

   //friend ostream& operator<< (ostream& in, const Socket& s) {
    //in << (string) s.toString();
    //return in;
  // }
 };
}
#endif 
