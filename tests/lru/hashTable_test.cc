#include <iostream>
#include <hashTable.inl>

using namespace std;

int main () {

	//NUMBER to NUMBER
	{
		hashTable<int,int> ht;
		int key_int[]   = {1,2,3,4,5,6,7,8,9,10,11,12};
		int value_int[] = {3,5,2,4,3,8,-1,5,2,5,6,2};


		// Pushing
		for (int i = 0; i < 10; i++) {
			ht.push (key_int[i] , value_int[i]);
		}

		//searching
		for (int i = 0; i < 10; i++) {
				if (!ht.get (key_int[i]))
					cout << __LINE__ << " SEARCH: DOESNT MATCH" << endl;
		}
		//getting
		for (int i = 0; i < 10; i++) {
			if (value_int[i] == ht.get (key_int[i]))
				cout << __LINE__ << " KEY: " << key_int[i] << " GET: " 
				<< ht.get (key_int[i]) << endl;
			else
				cout << __LINE__ << " GET: DOESNT MATCH" << endl;
		}
		//getting non exitency
		for (int i = 10; i < 15; i++) {
			if (value_int[i] == ht.get (key_int[i]))
				cout << __LINE__ << " KEY: " << key_int[i] << " GET: " 
				<< ht.get (key_int[i]) << endl;
			else
				cout << __LINE__ << " GET: DOESNT MATCH" << endl;
		}


		//Deleting


	}


}
