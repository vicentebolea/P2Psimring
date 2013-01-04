/* 
 This is just a sketch for the LRU class 
	I am wondering to use a hash table + singly linked list
	Since for the three operations that im using i 
	have theses complexities:
  
		 - push_front: O(1)
		 - pop_back:   O(1)
		 - search:     O(1 + n/k) 
			
	These complexities will be in the best case since the hash table
	will may rehash sometimes and in each rehash will take O(n).
 
	The way that im implementing this LRU is the next:
	 
		- The LL will just store the diskpage.
	 
		- The hash table given a key (wish in this experiment will be 
	   a set of number) will store pointers to each node of the LL. 

*/

#ifndef __LRU_INL_
#define __LRU_INL_

#include <list.inl>
#include <hashTable.inl>
#include <chain.inl>

template <class T>
class lru: public List<T> {
	protect:
	public:

};

#endif
