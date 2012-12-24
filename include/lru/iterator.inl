#ifndef __ITERATOR_H_
#define __ITERATOR_H_

#include <element.inl>

template <class T>
class Iterator {
	private:
		Element<T>* pointer;

	public:
		Iterator (): pointer(NULL) {}
		Iterator (const Iterator& it) {
			pointer = it.pointer;	
		}
		const Iterator& operator= (const Iterator& it) {
			pointer = it.pointer;
			return *pointer;
		}

		T* getPointer() const {
			return pointer;
		}
};

#endif
