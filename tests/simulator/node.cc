#include <exception>
#include <hashtable.hh>
#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <stdexcept>
#include <unittest++/UnitTest++.h>
#include <node.hh>

TEST (ctor) {
	Node& n = Node.getInstance();
}

//TEST (dtor) {
//}

TEST (init) {
	Node& n = Node.getInstance();
	n.init();
}

TEST (start) {
	Node& n = Node.getInstance();
	n.start();
}
