#ifndef __CHAIN_HH_
#define __CHAIN_HH_

#include <collector.inl>
#include <iterator.inl>
#include <iostream>

using std::cerr;
using std::endl;

template <class T>
class Chain: public List<T> {

	protected:
		struct Node<T>{
			T data;
			Node* link;
			Node<T> () : T(NULL), link(NULL){}
			Node<T> (const T& d, const Node* l = NULL)
			 : data(d), link(l) {}
		} *first, *last;

	public:
		class Iterator: public ::Iterator<Node<T> > {

			public:
				inline const Iterator& operator++ (int);
				inline const Iterator& operator++ ();
				inline const Iterator& operator* ();
		};

	public:
		Chain<T> ();
		~Chain<T> ();

		Chain<T> (const Chain<T>&);
		const Chain<T>& operator= (const Chain<T>&);

		bool push_back (const T&);
		bool push_front (const T&);

		const T& pop_back ();
		const T& pop_front ();

		bool remove (const T&);
		bool search (const T&) const;

		const Iterator& begin() const;
		const Iterator& end() const;
};

#ifndef __CHAIN_INL_
#include <chain.inl>
#endif

#endif
