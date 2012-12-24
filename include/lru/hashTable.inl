#ifndef __HASHTABLE_H_
#define __HASHTABLE_H_

/*******************************************
	Author: Vicente Adolfo Bolea Sanchez
	Email:  <vicente.bolea@gmail.com> ,
	        <vicente@unist.ac.kr>

	Hash function 32 bits:

	00000000 00000000 00000000 XXXXXXXX
	00000000 00000000 XXXXXXXX 00000000
	00000000 XXXXXXXX 00000000 00000000
	XXXXXXXX 00000000 00000000 00000000

	This hashTable uses chaining to store the 
	data.
	*******************************************/

#include <inttypes.h>
#include <stdint.h>

template <class T>
class hashTable: public List<T> {
	private:
		Chain<T>** table;

		uint32_t h (uint8_t*);

	public:
		hashTable ();
		~hashTable ();

		bool push (const T&);
		const T& pop ();

};

/* */
template <class T>
hashTable<T>::hashTable (size_t s) : List (s) {
	this->table = new Chain [size];
}

/* */
template <class T>
hashTable<T>::~hashTable () {
	delete this->table;
}

/* */
template <class T>
bool hashTable<T>::push (const T& d) {
	return table[h(&d)].push(d);
}

/* */
template <class T>
bool hashTable<T>::remove (const T& d) {
	return table[h(&d)].remove(d);
}

/* Simple hash function which can represent
	* less than 32 bits number, It uses modulo.
	*/
template <class T>
uint32_t hashTable<T>::h (uint8_t* s) {

	uint32_t key = 0;
	key += (uint32_t) s;
	key += (uint32_t) ((uint8_t) s[1] << 010);
	key += (uint32_t) ((uint8_t) s[2] << 020);  
	key += (uint32_t) ((uint8_t) s[3] << 030);  
	return key%size;
}

#endif
