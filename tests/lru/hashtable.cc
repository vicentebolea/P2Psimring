#include <exception>
#include <hashtable.hh>
#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <stdexcept>
#include <unittest++/UnitTest++.h>

using std::out_of_range;

struct htfixture {
	hashTable<int, int> ht;
	size_t size;

	htfixture() {
		size = 100;
		for (size_t i = 0; i < size; i++)
			ht.insert (i, i);
	}

	~htfixture () {}
};

SUITE (ht_test) {

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, insert) {

		CHECK_EQUAL (ht.getSize(), size);
	}

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, find) {
		for (int i = 0; i < 100; i++) {
			CHECK (ht.find (i));
		}
	}

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, remove) {

		for (int i = 0; i < 20; i++) {
			ht.remove (i);
			CHECK (!ht.find (i));
		}

		CHECK_EQUAL (ht.getSize(), (size_t) 80);
	}

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, lookup) {

		for (int i = 0; i < 100; i++)
			CHECK_EQUAL (ht.lookup (i), i);
	}

	// --------------------------------------------------------
	TEST (rehashing) {
		hashTable<int, int> ht (1);

		for (int i = 0; i < 1000; i++)
			ht.insert (i, i);

		for (int i = 0; i < 1000; i++)
			CHECK_EQUAL (ht.lookup (i), i);
	}

	// --------------------------------------------------------
	TEST (stress_insert) {
		hashTable<int, int> ht (1);

		for (int i = 0; i < 1000000; i++)
			ht.insert (i, i);

		CHECK_EQUAL (ht.getSize(),(size_t) 1000000);
	}

	// --------------------------------------------------------
	TEST (stress_lookup) {
		hashTable<int, int> ht (1);

		for (int i = 0; i < 1000000; i++)
			ht.insert (i, i);

		for (int i = 0; i < 1000000; i++)
			CHECK_EQUAL (ht.lookup (i), i);
	}

}

SUITE (bad_ht_test) { 

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, bad_find) {
		for (int i = 100; i < 110; i++) 
			CHECK (!ht.find (i));
	}

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, bad_remove) {
		for (int i = 100; i < 110; i++) 
			ht.remove (i);

		CHECK_EQUAL (ht.getSize(), size);
	}

	// --------------------------------------------------------
	TEST_FIXTURE (htfixture, bad_lookup) {
		for (int i = 100; i < 110; i++) 
			CHECK_THROW (ht.lookup (i), out_of_range);
	}
}
