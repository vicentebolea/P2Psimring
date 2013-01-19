#include <iostream>
#include <stdio.h>
#include <file/parser.hh>
#include <string>

int main() {
	Parser parser ("test/minini_test.conf");
	printf ("PORT: %llu \n", parser.get_value_of ("network", "port"));
//	printf ("DOESNT EXIST: %llu \n", parser.get_value_of ("network", "house"));
}


