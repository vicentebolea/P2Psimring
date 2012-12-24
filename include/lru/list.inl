#ifndef __LIST_H_
#define __LIST_H_

#include <stddef.h>

template <class T>
class List {
	private:
		size_t size;

	public:
		List<T> () : size(0) {}
		List<T> (size_t s) : size(s) {}

		inline size_t getSize () const {
			return size;
		}

		inline bool empty () const {
			return size ? true: false;
		}

		virtual bool push_back (const T&) = 0;
		virtual const T& pop_front () = 0;

};

#endif
