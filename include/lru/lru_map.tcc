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

template <class key>
void Lru<key>::push (const key& k, const value& v) {

	if (!belong (k)) {
		ll.push_back (k, v);
		ht.push (k, ll.end());
		size++
	}

	if (size > max) pop();
}

template <class key>
void Lru<key, value>::pop (const key& k) {

	list<value>::iterator it = ll.begin();
	ht.remove ((*it).key);
	ll.pop_front();
}

template <class key, class value>
bool Lru<key, value>::find (const key& k) {
	return ht.search (k);
}

#endif
