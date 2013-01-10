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
 * This is just a sketch for the LRU map class 
 * I am wondering to use a hash table + doubly linked list
 * Since for the three operations that im using i 
 * have theses complexities:
 *
 *  - insert:   O(1)
 *  - lookup:   O(1)
 *  - pop:      O(1) 
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

#include <collection.hh>
#include <hashtable.hh>

#include <stdexcept>
#include <algorithm>
#include <list>

using std::pair;
using std::list;
using std::out_of_range;

/** --------------------------------------------------------
 * @class lru_map <lru_map.hh>
 * @see hashtable <hashtable.hh>
 */
template <class key, class value>
class lru_map: public Collection {

 public:
  lru_map (size_t _max) : max (_max) {}

  void insert (const key&, const value&);
  const value& lookup (const key&) throw (out_of_range);
  void pop (void);
  const value& front (void);

 protected:
  void update (const key&, const value&) throw (out_of_range);

 protected:
  size_t max;

  list<pair<key, value> > ll;
  hashTable<key, typename list<value>::iterator> ht;
};

#include <lru_map.tcc>

#endif
