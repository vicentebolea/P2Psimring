#include <iostream>
#include "../include/exception.hh"


using namespace std;

int main() {
	int a = 2;
	try {
		if (a != 3)
			throw NetException("NOT three");

	} catch (Exception& e) {
		cerr << e << endl;
		cerr << e.backTrace() << endl;
	}

	return 0;
}
