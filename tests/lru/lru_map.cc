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
		CHECK_EQUAL (lm.getSize(), (size_t)50);
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, lookup) {
  for (int i = 50; i < 100; i++)
			CHECK_EQUAL (lm.lookup(i), i); 
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, pop) {
  for (int i = 0; i < 20; i++)
			lm.pop();
  
		CHECK_EQUAL (lm.getSize(), (size_t)30);
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, oldest) {
  for (int i = 0; i < 20; i++)
			lm.pop();
		
		CHECK_EQUAL (lm.oldest(), 70);
	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, newest) {
  for (int i = 0; i < 20; i++)
			lm.pop();
		
		CHECK_EQUAL (lm.newest(), 99);
	}

	TEST_FIXTURE (lmfixture, lru) {
  for (int i = 50; i < 60; i++) {
				lm.lookup (i);
				CHECK_EQUAL (lm.newest(), i);
		}
	}

	TEST (stress_push) {
		lru_map<int, int> lm (500);
		for (int i = 0; i < 1000000; i++)
			lm.insert (i, i);

		CHECK_EQUAL (lm.getSize(), (size_t)500);
		CHECK_EQUAL (lm.newest(), 999999);
	}

	//TEST (stress_lookup) {
		//lru_map<int, int> lm (500);
		//for (int i = 0; i < 1000000; i++)
			//lm.insert (i, i);
//
		//for (int i = 0; i < 1000000; i++)
			//lm.insert (i, i);
		//CHECK_EQUAL (lm.getSize(), (size_t)500);
		//CHECK_EQUAL (lm.newest(), 999999);
	//}
}

SUITE (lru_map_bad) {

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, lookup) {
  for (int i = 0; i < 50; i++)
			CHECK_THROW (lm.lookup(i), out_of_range); 

	}

 // -------------------------------------------------------
	TEST_FIXTURE (lmfixture, pop) {
  for (int i = 0; i < 50; i++)
			lm.pop();

  for (int i = 0; i < 100; i++) {
			lm.pop();
			CHECK_EQUAL (lm.getSize(), (size_t)0);
		}

	}

 // -------------------------------------------------------
	//TEST (front) {
//
	//}
}
