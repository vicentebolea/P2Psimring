#include <unittest++/UnitTest++.h>
#include <lru_map.hh>
#include <exception>
#include <stdexcept>
#include <iostream>

using std::out_of_range;

struct lmfixture {
	lru_map<int, int> lm;
	int size;

	lmfixture() : lm (50) {
		size = 100;
		for (int i = 0; i < size; i++)
			lm.insert (i, i);
	}

	~lmfixture () {}
};

SUITE (lru_map_basic) {

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, insert) {
		CHECK_EQUAL (lm.getSize(), 100);
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, lookup) {
  for (int i = 0; i < 100; i++)
			CHECK_EQUAL (lm.lookup(i), i); 

	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, pop) {
  for (int i = 0; i < 20; i++)
			lm.pop();
  
		CHECK_EQUAL (lm.getSize(), 80);
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, oldest) {
  for (int i = 0; i < 20; i++)
			lm.pop();
		
		CHECK_EQUAL (lm.oldest(), 70);
	}
	TEST_FIXTURE (lmfixture, newest) {
  for (int i = 0; i < 20; i++)
			lm.pop();
		
		CHECK_EQUAL (lm.newest(), 70);
	}
}

//SUITE (lru_map_bad) {
//
// // -------------------------------------------------------
//	TEST (insert) {
//
//
//	}
//
// // -------------------------------------------------------
//	TEST (lookup) {
//
//	}
//
// // -------------------------------------------------------
//	TEST (pop) {
//
//	}
//
// // -------------------------------------------------------
//	TEST (front) {
//
//	}
//}

int main () {
	return UnitTest::RunAllTests();
}
