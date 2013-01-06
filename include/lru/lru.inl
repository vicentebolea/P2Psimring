/* 
 This is just a sketch for the LRU class 
	I am wondering to use a hash table + singly linked list
	Since for the three operations that im using i 
	have theses complexities:
  
		 - push_front: O(1)
		 - pop_back:   O(1)
		 - search:     O(1 + n/k) 
			
	These complexities will be in the best case since the hash table
	will may rehash sometimes and in each rehash will take O(n + buckets).
 
	The way that im implementing this LRU is the next:
	 
		- The LL will just store the diskpage.
	 
		- The hash table given a key (wish in this experiment will be 
	   a set of number) will store pointers to each node of the LL. 

*/

#ifndef __LRU_INL_
#define __LRU_INL_

#include <collection.inl>
#include <hashTable.inl>
#include <list>

using std::list;

template <class key, class value>
class Lru: public Collection {

	protect:
		struct entry {
			key key_n;
			value val_n;
			entry (const key& k, const value& v) key_n(k), val_n(v) {}
		};

	 size_t max;
		hashTable<key, list<value>::iterator> ht;
		list<entry> ll;

	public:
  Lru (size_t _max) max (_max) {}
	
		void push (const key&, const value&);
		void pop ();

		bool belong (const key&);

};

template <class key, class value>
void Lru<key, value>::push (const key& k, const value& v) {

	if (!belong (k)) {
		ll.push_back (k, v);
		ht.push (k, ll.end());
		size++
	}

	if (size > max) pop();
}

template <class key, class value>
void Lru<key, value>::pop (const key& k) {

	list<value>::iterator it = ll.begin();
	ht.remove ((*it).key);
	ll.pop_front();
}

template <class key, class value>
bool Lru<key, value>::belong (const key& k) {
	return ht.search (k);
}

#endif
