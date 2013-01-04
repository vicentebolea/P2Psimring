#include <stdio.h>
#include <iostream>
#include <server/client_e.hh>

using namespace std;

int main() {
	Client_e client;


	try { 
		client.connect(-1);
	} catch (Exception& e) {
		cout << e << endl;
		cout << client << endl;
	}
}
