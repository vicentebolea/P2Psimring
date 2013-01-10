#ifndef __ELEMENT_INL_
#define __ELEMENT_INL_

template <class T>
struct Element {
	T data;
	Element<T>* link;

	Element () {
		data = link = NULL;
	}
	Element (const T& d) {
		data = d;
		link = NULL;
	}
	~Element () {
	//	delete data;
	}
	Element (const T& t, Element* l): data(t), link(l) {}
	Element (const Element& e) {
		data = e.data;
		link = e.link;
	}

};


#endif
