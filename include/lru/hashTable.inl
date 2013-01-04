/**
	* Author: Vicente Adolfo Bolea Sanchez
	* Email:  <vicente.bolea@gmail.com>,
	*         <vicente@unist.ac.kr>
	*
	* This is the implementation of a hash table
	* this hash table uses a linked list to prevent
	* colisions this is chained hash table.
 *
 * Also to keep a good load factor the hash table
	* will be resize whenever the load factor is over
	* 150%.
	* For this matter I use another linkedlist to
	* keep track of all the keys stores, then I can iterate
	* Over the table.
	* 
	* For now I am using a simple hash function which
	* just break the four first bytes of the key 
	* and apply mod with the bucket's table length.
	*
	* Hash function 32 bits:
	* 
	* 00000000 00000000 00000000 XXXXXXXX
	* 00000000 00000000 XXXXXXXX 00000000
	* 00000000 XXXXXXXX 00000000 00000000
	* XXXXXXXX 00000000 00000000 00000000
	* 
	* KEY ----------------------> entry 
	*      buckets [hash (KEY)]
	*
	* Here is the model that I used to implement 
	* this hash table: 
	*
	* key | hash(KEY) |     buckets [hash (KEY)]
	* ----|-----------|------------------------------
	*
	*                 +------+--------+-------------+
	* KEY5 --+  +---->| KEY1 | VALUE1 |link to entry|
	*        |  |     +------+--------+-------------+
	* KEY1 --+--+ +-->| KEY2 | VALUE2 |link to entry|
	*        |    |   +------+--------+-------------+
	* KEY3 --+----+-->| KEY3 | VALUE3 |link to entry|
	*        |    |   +------+--------+-------------+
	* KEY2 --+----+   | KEY4 | VALUE4 |link to entry|
	*        |        +------+--------+-------------+
	*        +------->| KEY5 | VALUE5 |link to entry|
	*                 +------+--------+-------------+
	*
	*/

#ifndef __HASHTABLE_INL_
#define __HASHTABLE_INL_

#include <collection.hh>

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h> //for size_t

// Cant believe that the c++ compiler does not recognize
// size_t, bool and another primitive types..
// aim to make this language hard

template <class key, class value>
class hashTable: public Collection {

protect:
	struct entry {
		key key_n;
		entry value_n;
		node (const key& k, const value& v) {
			key = k;
			value = value;
		}
	};

	Chain<entry>* buckets;
	Chain<key> stored_keys;
	size_t buckets_no;

	inline double load_factor (void) const;
	inline uint32_t h (uint8_t*, size_t) const;
	void rehash (void);

	public:
	hashTable ();
	~hashTable ();

	bool push (const key&, const value&);
	bool remove (const key&);
	bool search (const key&);
};


/* */
template <class key, class value>
hashTable<key, value>::hashTable () {
	buckets_no = 128;
	buckets = new Chain [buckets_no];
}


/* */
template <class key, class value>
hashTable<key, value>::~hashTable () {
	delete this->table;
}


/* */
template <class key, class value>
inline double hashTable<key, value>::load_factor () {
	return (double)(buckets_no/size);
}


/* 
	* This method will resize the hash table 
	* to the double of the current size.
	*
	* First it will create a new table and it
	* will be filled with the old elements and keys
	* After that the old table is remove.
	*/
template <class key, class value>
void hashTable<key, value>::rehash () {

	buckets_no *= 2;
	Chain<T>* tmp_b = new Chain [buckets_no];

	Chain::Iterator it;
	for (it = Chain.begin(); it != Chain.end(); it++) {
		size_t key = h (it.getValue(), buckets_no/2);
		tmp_b->push (key, buckets [key]);
	}

	delete [] buckets;
	buckets = tmp_b;
}

/* */
template <class key, class value>
bool
hashTable<key, value>::push (const key& k, const value& v) {

	if (buckets[h(k)]->push(v)) {
		size++;
		stored_keys.push(k);
		return true;

	} else {
		return false;
	}
}


/* */
template <class key, class value>
bool 
hashTable<key, value>::remove (const key& k, const value& v) {
	return table[h(k)].remove(v);
}

/* Simple hash function which can represent
	* less than 32 bits number, It uses modulo.
	*/
template <class key, class value>
	inline uint32_t
hashTable<key,value>::h (uint8_t* s, size_t size = buckets_no)
{
	uint32_t key = 0u;
	key += (uint32_t) s;
	key += (uint32_t) ((uint8_t) s[1] << 010u);
	key += (uint32_t) ((uint8_t) s[2] << 020u);  
	key += (uint32_t) ((uint8_t) s[3] << 030u);  
	return key%size;
}

#endif
