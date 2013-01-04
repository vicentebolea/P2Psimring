#ifndef __CHAIN_INL_
#define __CHAIN_INL_

#include <chain.hh>

/******************************************/
/* OBJECTS LIFE METHODS                   */
/******************************************/

/* */
template <class T>
Chain<T>::Chain (): List<T>() {
	first = last = NULL;
}

/* */
template <class T>
Chain<T>::~Chain<T> () {
	Node* tmp = first; 

	while (tmp != NULL) {
		Node* current = tmp;
		tmp = tmp->link;
		delete current;
	}
}

/******************************************/
/* ITERATOR METHODS                       */
/******************************************/

template <class T>
inline const Chain<T>::Iterator&
Chain<T>::Iterator::operator++ (int) {
 Iterator aux = *this;
	pointer = pointer->link;
	return aux;
}

template <class T>
inline const Chain<T>::Iterator&
Chain<T>::Iterator::operator++ () {
	pointer = pointer->link;
	return *this;
}

template <class T>
inline const T&
Chain<T>::Iterator::operator* (int) {
	return pointer.data;
}

/******************************************/
/* CHAIN EXPECIFICS METHODS               */
/******************************************/

/* */
template <class T>
bool Chain<T>::push_back (const T& data) {
	try {

		if (getSize<T>() == 0)
			first = last = new node(data);

		else if (getSize() == 1)

		else

	} catch (bad_alloc& e) {
		cerr << e.what() << endl;
	}
}

/* */
template <class T>
bool Chain<T>::push_front (const T& data) {
}

/* */
template <class T>
const T& Chain<T>::pop_back () {
}

/* */
template <class T>
const T& Chain<T>::pop_front () {
}

/* */
template <class T>
bool Chain<T>::remove (const T& data) {
}

/* */
template <class T>
bool Chain<T>::search (const T& data) const {
}

#endif
