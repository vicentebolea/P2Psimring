#include <stdio.h>
#include <iostream>
#include <server/server.hh>

const int port = 1992;
const int nservers = 10;

int main () {

	Server a (port, nservers);
	std::cout << a << std::endl;

	return 0;
}
