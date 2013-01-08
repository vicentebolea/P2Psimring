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
	* Nevertheless I am not rehashing to reduce the size
 *
	* For this matter I wonder to use another linkedlist to
	* keep track of all the keys stores, then I can iterate
	* over the table.
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

#include <list>
#include <algorithm>
#include <stdexcept>
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h> //for size_t
#include <assert.h> //for size_t

using std::list;
using std::out_of_range;

template <class key, class value>
class hashTable: public Collection {

	public:
		hashTable (size_t);
		~hashTable ();

		bool push (const key&, const value&);
		void remove (const key&);
		bool search (const key&);
		const value& at (const key&) throw (out_of_range);

	protected:
		struct entry {
			key key_n;
			value value_n;
			entry (const key& k, const value& v) {
				key_n = k;
				value_n = v;
			}
		};

		// Functor to search a key in a given list	
		struct match_key {
			key master_key;
			bool found;

			match_key (const key& k) : master_key(k), found(false) {}
			bool operator () (const entry& e) {
				found = (master_key == e.key_n);
				return (master_key == e.key_n);
			}

			bool is_found() { return found; }
		};

		list<entry>* buckets;
		size_t buckets_no;

		const static double threshold = 1.5;
		inline double over_threshold (void) const;

		inline uint32_t h (const key&, size_t) const;
		void rehash (void);
};


/* */
template <class key, class value>
hashTable<key, value>::hashTable (size_t _size = 128) {
	assert (size == 0);
	buckets_no = _size;
	buckets = new list<entry> [buckets_no];
}


/* */
template <class key, class value>
hashTable<key, value>::~hashTable () {
	delete[] buckets;
}


/************************************************/
/* PRIVATE METHODS FOR REHASHING                */
/************************************************/

/* */
template <class key, class value>
inline double hashTable<key, value>::over_threshold () const {
	return (double)(size/buckets_no) >= threshold;
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

	list<entry>* old_buckets    = buckets;
	size_t       old_buckets_no = buckets_no;

	buckets_no *= 2;
	buckets = new list<entry> [buckets_no];

	//For each list of entries
	for (size_t i = 0; i < old_buckets_no; i++) {

		if (!old_buckets[i].empty()) {
			typename list<entry>::iterator it;
			list<entry>& b = old_buckets[i];

			//Copy all the entries of the list
			for (it = b.begin(); it != b.end(); it++) {
				size_t new_key = h ((*it).key_n);
				buckets [new_key].push_back (*it);
			}
		}
	}
	delete [] old_buckets;
}

/************************************************/
/*       PUBLIC METHODS                         */
/************************************************/

/* */
template <class key, class value>
bool
hashTable<key, value>::push (const key& k, const value& v) {
	uint32_t key_n = h(k);

	if (search (k))
		return false;

	else {
		buckets[key_n].push_back (entry(k,v));
		size++;

		if (over_threshold()) rehash();

		return true;
	}
}

/**
	*
	*/
template <class key, class value>
void
hashTable<key, value>::remove (const key& k) {
	buckets [h(k)].remove_if (match_key(k));
}

/**
	*
	*/
template <class key, class value>
const value&
hashTable<key, value>::at (const key& k) throw (out_of_range)
{
	list<entry>& l = buckets[h(k)];
	typename list<entry>::iterator it;

	it = find_if (l.begin(), l.end(), match_key(k));
	if (it == l.end())
		throw out_of_range ("Doesnt belong");
	else
		return (*it).value_n;
}

/**
	*
	*/
template <class key, class value>
bool 
hashTable<key, value>::search (const key& k) {
	list<entry>& t = buckets [h(k)];
	return find_if(t.begin(), t.end(), match_key(k)) != t.end();
}


/** Simple hash function which can represent
	* less than 32 bits number, It uses modulo.
	*/
template <class key, class value>
inline uint32_t
hashTable<key, value>::h (const key& k, size_t length = 0) const
{
	uint8_t* seed = (uint8_t*) &k;
	uint32_t _key = 0;

	if (!length) length = buckets_no;

	for (size_t i = 0; i < sizeof(key) % 5; i++)
		_key += (uint32_t) (seed[i] << (0x8 * i));

	return _key % length;
}

#endif
