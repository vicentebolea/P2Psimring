#ifndef __CHAIN_H_
#define __CHAIN_H_

#include <list.inl>
#include <element.inl>
#include <iterator.inl>
#include <iostream>

using std::cerr;
using std::endl;

template <class T>
class Chain: public List<T> {
	private:
		Element<T> *first, *last;

	public:
		typedef Element<T> node;
		class Iterator_chain: public Iterator<T> {
			public:
		};
		Chain<T> ();
		~Chain<T> ();

		bool push_back (const T&);
		bool push_front (const T&);

		const T& pop_back ();
		const T& pop_front ();

		bool remove (const T&);
		bool search (const T&) const;

		const Iterator_chain& begin() const;
		const Iterator_chain& end() const;
};

/* */
template <class T>
Chain<T>::Chain (): List<T>() {
	first = last = NULL;
}

/* */
template <class T>
Chain<T>::~Chain<T> () {
	node* tmp = first; 

	while (tmp != NULL) {
		node* current = tmp;
		tmp = tmp->link;
		delete current;
	}
}

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
