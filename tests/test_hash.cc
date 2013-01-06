#include <iostream>
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
using namespace std;

template <class key>
inline uint32_t h (const key& k, size_t _size = 0) {
 uint8_t* seed = (uint8_t*) &k;

	uint32_t _key = 0;
	for (size_t i = 0; i < sizeof(key) % 5; i++)
		_key += (uint32_t) (seed[i] << (0x8 * i));

	return _key % _size;
}

int main () {
	int a = 11;
	cout << "HASH OF " << a << " = " << h<int> (a, 5) << endl;
	cout << "size of a : " <<sizeof  a << endl;
}
