#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <stdint.h>
#include <limits.h>
#include <limits>
#include <inttypes.h>
#include <hashTable.inl>

using namespace std;

#define UINT32_MAX numeric_limits<uint32_t>::max() 

extern char* program_invocation_short_name;


inline void msg (const char* s, ...) {
	char input [128];
	char output [1024];
	va_list v1;

	va_start (v1, s);

	snprintf (output, 512, "%s|%s|%i::", 
			program_invocation_short_name,
			__FILE__, __LINE__);

	vsnprintf (input, 128, s, v1);

	strncat (output, input, 1024);
	fprintf (stdout, "TEST: %s\n", output);
}

int main () {

	int key_int[]   = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int value_int[] = {3,5,2,4,3,8,-1,5,2,5,6,2};
	int key_int_delete[] = {1,2,3,4,5};

	//////////////////////////////////////////////////
	//        BASIC TEST                            //
	//////////////////////////////////////////////////	
	{
		hashTable<int,int> ht;

		// Pushing
		cout << "PUSH TEST" << endl;
		for (int i = 0; i < 10; i++) {
			ht.push (key_int[i] , value_int[i]);
		}

		//searching
		cout << "SEARCH TEST" << endl;
		for (int i = 0; i < 10; i++) {
			if (!ht.search (key_int[i]))
				msg ("SEARCH: DOESNT MATCH");
		}
		//atting
		cout << "GET TEST" << endl;
		for (int i = 0; i < 10; i++) {
			try { 

				if (value_int[i] == ht.at (key_int[i]))
					msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));
				else
					msg ("GET: DOESNT MATCH KEY: %i GET %i",
					 key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}

		//atting non exitency
		cout << "AT NONEXISTENCY TEST" << endl;
		for (int i = 10; i < 15; i++) {

			try { 
				if (value_int[i] == ht.at (key_int[i]))
					msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));
				else
					msg ("GET: DOESNT MATCH KEY: %i GET %i",
					 key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}

		//Deleting
		cout << "DELETE TEST" << endl;
		for (int i = 0; i < 5; i++)
			ht.remove (key_int_delete [i]);

		for (int i = 0; i < 10; i++) {
			try {
				msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}
	}

	//////////////////////////////////////////////////
	//        REHASHING TEST                        //
	//////////////////////////////////////////////////	

	cout << "Rehashing test" << endl;
	{
		hashTable<int, int> ht (1);

		// Pushing
		cout << "PUSH TEST" << endl;
		for (int i = 0; i < 10; i++) {
			ht.push (key_int[i] , value_int[i]);
		}

		//searching
		cout << "SEARCH TEST" << endl;
		for (int i = 0; i < 10; i++) {
			if (!ht.search (key_int[i]))
				msg ("SEARCH: DOESNT MATCH");
		}
		//atting
		cout << "GET TEST" << endl;
		for (int i = 0; i < 10; i++) {
			try { 

				if (value_int[i] == ht.at (key_int[i]))
					msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));
				else
					msg ("GET: DOESNT MATCH KEY: %i GET %i",
					 key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}

		//atting non exitency
		cout << "AT NONEXISTENCY TEST" << endl;
		for (int i = 10; i < 15; i++) {

			try { 
				if (value_int[i] == ht.at (key_int[i]))
					msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));
				else
					msg ("GET: DOESNT MATCH KEY: %i GET %i",
					 key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}

		//Deleting
		cout << "DELETE TEST" << endl;
		for (int i = 0; i < 5; i++)
			ht.remove (key_int_delete [i]);

		for (int i = 0; i < 10; i++) {
			try {
				msg ("KEY: %i GET %i", key_int[i], ht.at (key_int[i]));

			} catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}
	}

	//////////////////////////////////////////////////
	//        STRESS TEST                           //
	//////////////////////////////////////////////////	

	cout << "STRESS TEST" << endl;
	{
		hashTable<int, int> ht (1);
		for (uint32_t i = 0; i < 1000000; i++) {
			ht.push (i, i);	
		}

		for (uint32_t i = 0; i < 1000000; i++) {
			try { ht.at (i); } catch (out_of_range& e) {
				msg ("AT TEST: NOT FOUND");
			}
		}
	}
	cout << "ALL TESTS DONE" << endl;
}