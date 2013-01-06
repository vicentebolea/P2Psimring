#include <iostream>
#include <hashTable.inl>

using namespace std;

int main () {

	//NUMBER to NUMBER
	{
		hashTable<int,int> ht;
		int key_int[]   = {1,3,4,2,5,6,1,2,4,5,6,2};
		int value_int[] = {1,3,4,2,5,6,1,2,4,5,6,2};


		// Pushing
		for (int i = 0; i < 10; i++) {
			ht.push (key_int[i] , value_int[i]);
		}

		//Searching
		for (int i = 0; i < 10; i++) {
			if (value_int[i] != ht.search (key_int[i]))
				cout << __LINE__ << " SEARCH: DOESNT MATCH" << endl;
		}

		//Deleting


	}


}
