#include <lru_map.hh>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <stdint.h>
#include <limits.h>
#include <limits>
#include <inttypes.h>

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

 //Basic TEST
 {
  lru_map<int, int> lm (10);

  cout << "PUSH TEST" << endl;
  for (int i = 0; i < 10; i++)
   lm.push (i,i);

  cout << "POP TEST" << endl;
  for (; !lm.empty(); lm.pop())
   cout << "ELEMENT " << lm.front () << endl;

  cout << "FIND TEST" << endl;
  for (int i = 0; i < 10; i++)
   lm.push (i,i);

  for (int i = 0; i < 10; i++)
   if (!lm.find (i))
    msg ("ERROR FIND METHOD");
 }

 {
  cout << "STRESS TEST" << endl;
  cout << "PUSH TEST" << endl;
  lru_map<int, int> lm (1000);

  for (int i = 0; i < 1000000; i++)
   lm.push (i,i);

  msg ("SIZE: %zi , front 999000 = %i \n", lm.getSize(), lm.front ());

  cout << "FIND TEST" << endl;
  for (int i = 999000; i < 1000000; i++) {
   if (!lm.find (i))
    msg ("ERROR FIND METHOD");
  }

  cout << "POP/FRONT TEST" << endl;
  for (int i = 999000; i < 1000000; i++) {
   if (i != lm.front())
    msg ("ERROR STRESS TEST: front: %i != %i", lm.front(), i);
   lm.pop();
  }
 }

 return 0;
}
