#ifndef __ITERATOR_H_
#define __ITERATOR_H_

//#include <element.inl>

template <class T>
class Iterator {
	protected:
		T* pointer;

	public:
		Iterator (): pointer(NULL) {}
		Iterator (const T* link) {
				pointer = link;
		}
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

		virtual const Iterator& operator++ (int) = 0;
		//virtual const Iterator& operator-- (int) = 0;
		virtual const Iterator& operator++ () = 0;
		//virtual const Iterator& operator-- () = 0;
		virtual const Iterator& operator* () = 0;
};

#endif
