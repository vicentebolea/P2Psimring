#include <exception>
#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <stdexcept>
#include <unittest++/UnitTest++.h>
#include <node.hh>

TEST (ctor) {
	Node n;
}

TEST (init) {
	Node n;
	n.init();
}

TEST (start) {
	Node n;
	n.init();
	n.start();
}
