#include <assert.h>
#include <chain.inl>
#include <stdio.h>
#include <stdlib.h>

int int_values[] = {
	1,2,3,451,1,4,5,6,3414,46,6,45,234,324,34,35,454,6,56576,
	768,78,7878,768,78,6787,687,8768,76,87876,4343,34,3434,34,
	232,32,323,23,32,323,232,32,32,32,323,23,232,32,32,32,32,
	32323,34,34,4,5,6,7,734,34,34,343,5,6,45,34,34,34,34,4567
};

int main (int argc, char** argv) {
	
	Chain<int> chain;

	assert(chain.empty() == true);
	assert(chain.getSize() == 0);

	for (int i = 0; i < sizeof(int)/sizeof(int_values); i++)
		assert(chain.push_back (int_values[i]) == true);

	for (int i = 0; i < sizeof(int)/sizeof(int_values); i++)
		assert(chain.pop_front() == int_values[i]);

	return EXIT_SUCCESS;
}
