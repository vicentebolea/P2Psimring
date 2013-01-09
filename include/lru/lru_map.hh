// SKETCH
/** -------------------------------------------------------
 * @author Vicente Adolfo Bolea Sanchez
 *         <vicente.bolea@gmail.com>,
 *         <vicente@unist.ac.kr>
 *
 * @file   lru_map.hh
 * @brief  Template header for lru_map ADT
 ** -------------------------------------------------------
 *
 * @section DESCRIPTION
 *
 * This is just a sketch for the LRU class 
 * I am wondering to use a hash table + doubly linked list
 * Since for the three operations that im using i 
 * have theses complexities:
 *
 *  - push_front: O(1)
 *  - pop_back:   O(1)
 *  - search:     O(1 + n/k) 
 *
 * These complexities will be in the best case since 
 * the hash table will may rehash sometimes and in each 
 * rehash will take O(n + buckets).
 *
 * The way that im implementing this LRU is the next:
 *
 *  - The LL will just store the diskpage.
 *
 *  - The hash table given a key (wish in this experiment
 *    will be a set of number) will store pointers to each 
 *    node of the LL. 
 *
 */

#ifndef __LRU_MAP_HH_
#define __LRU_MAP_HH_

#include <collection.inl>
#include <hashtable.hh>
#include <list>

using std::list;

template <class key, class value>
class Lru: public Collection {

 public:
  Lru (size_t _max) : max (_max) {}

  void push (const key&);
  void pop ();

  bool find (const key&);


protect:
  struct entry {
   key key_n;
   value val_n;
   entry (const key& k, const value& v) : 
    key_n(k), val_n(v) {}
  };

  size_t max;
  hashTable<key, list<value>::iterator> ht;
  list<entry> ll;

};

#include <lru_map.tcc>

#endif
