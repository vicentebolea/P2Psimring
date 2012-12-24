#include <client.hh>
#include <stdio.h>
#include <unistd.h>

Client::Client(char* ip, int port) {
				host = gethostbyname (ip);

				sin_family = AF_INET;     
				sin_port = htons (port);   
				inet_pton (AF_INET, ip, &sin_addr);
				sin_addr = *((struct in_addr *)host->h_addr);
				bzero (&sin_zero, 8); 

				if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
								perror ("Socket");
								exit (EXIT_FAILURE);
				}
}

Client::~Client() {
	close (sock);
}

bool Client::connect() {
				if (::connect (sock, (struct sockaddr *)this,
																sizeof(struct sockaddr)) == -1) {
								perror("Connect error"); return false; }
				else 
					return true;
}
