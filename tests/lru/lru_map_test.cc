#include <unittest++/UnitTest++.h>
#include <lru_map.hh>
#include <exception>
#include <stdexcept>
#include <iostream>

struct lmfixture {
	lru_map<int, int> ht;
	int size;

	htfixture() {
		size = 100;
		for (int i = 0; i < size; i++)
			ht.insert (i, i);
	}

	~htfixture () {}
};

SUITE (lru_map_basic) {
	TEST_FIXTURE (lm, insert) {
		CHECK_EQUAL (lm.getSize(), 100);
	}

	TEST_FIXTURE (lm, lookup) {
  for (int i = 0; i < 100; i++)
   lm.push (i,i);

	}

	TEST (pop) {

	}

	TEST (front) {

	}
}

SUITE (lru_map_bad) {
	TEST (insert) {


	}

	TEST (lookup) {

	}

	TEST (pop) {

	}

	TEST (front) {

	}
}

int main () {
	return UnitTest::RunAllTests();
}
