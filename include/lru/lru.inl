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
		hashTable<key, bool> ht;
		list<value> ll;
		list<key> llk;

	public:
  Lru (size_t s) : Collection (s) {}
	
		void push (const key&, const value&);
		void pop ();

		bool belong (const key&);
};

template <class key, class value>
void Lru<key, value>::push (const key& k, const value& v) {

	if (ll.belong (k)) {
		ll.push_back (value);
		size++
	}
	if (size > max)
		pop();
}

template <class T>
void Lru<key, value>::pop (const key& k) {
	ll.pop_front();
	key* k = llk.front()

	ht.remove (k); 
	llk.pop();
}

template <class key, class value>
bool Lru<key, value>::belong (const key& k) {
	return ht.search (k);
}

#endif
