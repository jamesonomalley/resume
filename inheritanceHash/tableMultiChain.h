/*
	Name:	Jameson O'Malley
	Date:	12/2/2018
	File:   tableMultiChain.h
	Descr:
	Derived template class (from tableChain) to allow multiple hash keys
	with different data values.
*/
#ifndef tableMultiChain_H
#define tableMultiChain_H
#include <cstdlib>    // Provides size_t
#include "tableChain.h"         // Provides base hash table class with chaining
using namespace std;

// derived template class
template <class RecordType>
class tableMultiChain : public tableChain <RecordType> {
public:
	// override base class method since duplicates allowed
	// add entry at *end* of duplicate keys
	void insert(const RecordType& entry) override;
	// additional method to remove all entries for given key
	void remove_all(int key);
	// additional method to count number of entries for given key
	size_t count(int key) const;
	// additional method to display all entries for given key
	void display_key_values(int key) const;
	
};

// ***ADD METHOD DEFINITIONS HERE***
template <class RecordType>
void tableMultiChain<RecordType>::insert(const RecordType& entry) {
	assert(entry.key >= 0);
	hashNode<RecordType> *cursor = tableMultiChain<RecordType>::data[tableChain<RecordType>::hash_func(entry.key)];
	hashNode<RecordType> *precursor = nullptr;
	
	// find the key
	// update cursor to found key and precursor to node before cursor
	while ((cursor != nullptr) && ((cursor->data).key != entry.key)) {
		precursor = cursor;
		cursor = cursor->link;
	}

	// no duplicates
	if (cursor == nullptr) {
		list_head_insert(tableChain<RecordType>::data[tableChain<RecordType>::hash_func(entry.key)], entry);
		tableChain<RecordType>::total_records++;
	}
	// puts duplicate key/s at the end
	else {
		while ((cursor != nullptr) && ((cursor->data).key == entry.key)) {
			precursor = cursor;
			cursor = cursor->link;
		}
		list_insert(precursor, entry);
		tableChain<RecordType>::total_records++;
	}
}

// Goes through all entries to find and remove it
template <class RecordType>
void tableMultiChain<RecordType>::remove_all(int key) {
	assert(key >= 0);
	hashNode<RecordType> *cursor = tableMultiChain<RecordType>::data[tableMultiChain<RecordType>::hash_func(key)];
	hashNode<RecordType> *precursor = nullptr;

	// locate the key and update cursor to found key and precursor to node before cursor
	while ((cursor != nullptr) && ((cursor->data).key != key)) {
		precursor = cursor;
		cursor = cursor->link;
	}
	// cursor found after head 
	if ((cursor != nullptr) && (precursor != nullptr)) {
		list_remove(precursor);
		tableMultiChain<RecordType>::total_records--;
		// find more entries with same key?
		tableMultiChain<RecordType>::remove_all(key);
	}
	else if (cursor != nullptr) {
		// cursor is head
		list_head_remove(tableMultiChain<RecordType>::data[tableMultiChain<RecordType>::hash_func(key)]);
		tableMultiChain<RecordType>::total_records--;
		// find more entries with same key?
		tableMultiChain<RecordType>::remove_all(key);
	}
}

// Goes through all entries to find each value with the key 
template <class RecordType>
typename size_t tableMultiChain<RecordType>::count(int key) const {
	size_t i = 0;
	hashNode<RecordType> *cursor = tableMultiChain<RecordType>::data[tableMultiChain<RecordType>::hash_func(key)];
	// loops through
	while (cursor != nullptr) {
		if ((cursor->data).key == key) {
			i++;
		}
		cursor = cursor->link;
	}
	// return amount of keys found
	return i;
}

// Goes through all entries to find each value with the key and display it.
template <class RecordType>
void tableMultiChain<RecordType>::display_key_values(int key) const {
	assert(key >= 0);
	hashNode<RecordType> *cursor = tableMultiChain<RecordType>::data[tableMultiChain<RecordType>::hash_func(key)];
	size_t i = 0;

	// loops through
	while (cursor != nullptr) {
		// finds first value with given key
		if ((cursor->data).key == key && i == 0) {
			cout << "\tHashed index =" << tableMultiChain<RecordType>::hash_func(key) << " Data =" << (cursor->data).data;
			++i;
		}
		// finds the following values with given key
		else if ((cursor->data).key == key) {
			cout << " Data =" << (cursor->data).data;
		}
		cursor = cursor->link;
	}
	cout << endl;
}
#endif
/*
Starting table size is 12

***DISPLAY ALL TABLE ENTRIES***
Index = 0
KEY=811 DATA=100
Index = 1
KEY=1623 DATA=11
KEY=1 DATA=11.1
KEY=1 DATA=11.2
KEY=1 DATA=11.3
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
KEY=2 DATA=22.1
KEY=2 DATA=22.2
Index = 3
KEY=3 DATA=33.1
KEY=3 DATA=33.2
KEY=4058 DATA=33.9

***TEST CASE #1***
-->no matching key
-->removing 0 links; KEY = 0


-->SUCCESS: table size is now 12

***DISPLAY ALL TABLE ENTRIES***
Index = 0
KEY=811 DATA=100
Index = 1
KEY=1623 DATA=11
KEY=1 DATA=11.1
KEY=1 DATA=11.2
KEY=1 DATA=11.3
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
KEY=2 DATA=22.1
KEY=2 DATA=22.2
Index = 3
KEY=3 DATA=33.1
KEY=3 DATA=33.2
KEY=4058 DATA=33.9

***TEST CASE #2***
-->one matching key
-->removing 1 links; KEY = 811
Hashed index =0 Data =100

-->SUCCESS: table size is now 11

***DISPLAY ALL TABLE ENTRIES***
Index = 1
KEY=1623 DATA=11
KEY=1 DATA=11.1
KEY=1 DATA=11.2
KEY=1 DATA=11.3
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
KEY=2 DATA=22.1
KEY=2 DATA=22.2
Index = 3
KEY=3 DATA=33.1
KEY=3 DATA=33.2
KEY=4058 DATA=33.9

***TEST CASE #3***
-->three matching keys from middle
-->removing 3 links; KEY = 1
Hashed index =1 Data =11.1 Data =11.2 Data =11.3

-->SUCCESS: table size is now 8

***DISPLAY ALL TABLE ENTRIES***
Index = 1
KEY=1623 DATA=11
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
KEY=2 DATA=22.1
KEY=2 DATA=22.2
Index = 3
KEY=3 DATA=33.1
KEY=3 DATA=33.2
KEY=4058 DATA=33.9

***TEST CASE #4***
-->two matching keys from end
-->removing 2 links; KEY = 2
Hashed index =2 Data =22.1 Data =22.2

-->SUCCESS: table size is now 6

***DISPLAY ALL TABLE ENTRIES***
Index = 1
KEY=1623 DATA=11
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
Index = 3
KEY=3 DATA=33.1
KEY=3 DATA=33.2
KEY=4058 DATA=33.9

***TEST CASE #5***
-->two matching keys from beginning
-->removing 2 links; KEY = 3
Hashed index =3 Data =33.1 Data =33.2

-->SUCCESS: table size is now 4

***DISPLAY ALL TABLE ENTRIES***
Index = 1
KEY=1623 DATA=11
KEY=5678 DATA=11.4
Index = 2
KEY=2435 DATA=22
Index = 3
KEY=4058 DATA=33.9
Press any key to continue . . .
*/