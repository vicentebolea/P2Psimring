#include <unittest++/UnitTest++.h>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <socket_stream.hh>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

class ss_server {
 public: 
  int fd;
  int sock;

  ss_server () {
   connect ();
  }

  void connect () {
   int op;
   op = 1;
   sockaddr_in i;

   sock = socket (AF_INET, SOCK_STREAM, 0);
   setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &op, sizeof( int)); 

   i.sin_family = AF_INET;
   i.sin_port = htons (9999);
   i.sin_addr.s_addr = INADDR_ANY;
   bzero (&(i.sin_zero), 8);

   bind (sock, (struct sockaddr *)&i, sizeof(sockaddr));
   listen (sock, 12);
   fd = accept (sock, NULL, NULL);
  }

  ~ss_server () {
   close (fd);
   close (sock);
  }

};

SUITE (ss_suite) {
 TEST (constructor) {
  socket_stream ss (0);
 }

 TEST_FIXTURE (ss_server, recieve) {
  socket_stream ss (fd);
  char out = ss.recieve<char>();
  CHECK_EQUAL (out, 'H');
 }

 TEST_FIXTURE (ss_server, send) {
  socket_stream ss (fd);
  ss.send<char, 1> ('L'); 
 }
}

int main () {
 return UnitTest::RunAllTests();
}

