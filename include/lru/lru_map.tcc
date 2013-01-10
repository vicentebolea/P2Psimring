/** -------------------------------------------------------
 * @author Vicente Adolfo Bolea Sanchez
 *         <vicente.bolea@gmail.com>,
 *         <vicente@unist.ac.kr>
 *
 * @file   lru_map.hh
 * @brief  Template header for lru_map ADT
 ** -------------------------------------------------------
 *
 */

#ifndef __LRU_MAP_TCC_	
#define __LRU_MAP_TCC_	

////////////////////////  PUBLIC   /////////////////////////


/** --------------------------------------------------------
 * Push back in the linked list the given value and store
 * the key and the address of that value in the hash table.
 * In case that the pair is already in the list it will 
 * be moved to the newest position
 *
 * @param  A given key
 * @param  An Object paired with the previous key
 * @return void
 */
template <class key, class value>
void lru_map<key, value>::push (const key& k, const value& v) {

 if (!ht.search (k)) {
  ll.push_back (k,v);
  ht.push (k, --ll.end()); // :TRICKY: end() returns the last?
  size++;

 } else {
  update (k, v);
 }

 if (size > max) pop();
}


/** --------------------------------------------------------
 * Remove the older element of the list and its reference in
 * the hash table.
 */
template <class key, class value>
void lru_map<key, value>::pop () {

 key k (ll.begin().first);
 ht.remove (k);

 ll.pop_front();
 size--;
}


/** --------------------------------------------------------
 * @return  The oldest element of the LRU_map
 */
template <class key, class value>
const value& lru_map<key, value>::front () {
 return ll.front().second;
}

/** --------------------------------------------------------
 * This method will search the value of the given key. 
 * If it is found, It will remove the element and push into 
 * the last position of the list, e.g. the newest element.
 * 
 * @return  The value paired with the given key
 */
template <class key, class value>
const value&
lru_map<key, value>::get (const key& k) throw (out_of_range) {

 typename list<value>::iterator it = ht.at (k);
 value& tmp ((*it).second);
 update (k, tmp);

 return tmp;
}

////////////////////////  PRIVATE   /////////////////////////

/** --------------------------------------------------------
 * @param  A key paired with the value that your are looking 
 *         for
 */
template <class key, class value>
void
lru_map<key, value>::update (const key& k, const value& v)
 throw (out_of_range) 
{
 // :TRICKY:
 typename list<value>::iterator it = ht.at (k);

 ht.remove (k);         // Delete to the hash table
 ll.erase (it);         // Delete that node in the list
 size--;
 push (k, v);           // Rearrange the list
}

#endif
