/*
 * Simple interface of containers.
	* Expecify what it should do
	*
	*/
#ifndef __COLLECTION_INL_
#define __COLLECTION_INL_

#include <stddef.h>

//template <class T>
class Collection {
	protect:
		size_t size;

	public:
		Collection /*<T>*/ () : size(0) {}

		inline size_t getSize () const {
			return size;
		}

		inline bool empty () const {
			return size ? true: false;
		}
};

#endif
