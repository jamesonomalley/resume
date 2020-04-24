/*
	Author: Jameson O'Malley
	Date: 09/12/2018
	File: sequenceFixed.cpp
	Desc: Implementation file for the sequenceFixed class
*/
#include "sequenceFixed.h"
#include <cassert>

// default constructor
//postcondition: initialize to an empty sequenceFixed
sequenceFixed::sequenceFixed() : used(0), current_index(0) {}

// constant function to return number of items used
sequenceFixed::size_type sequenceFixed::size() const {
	return used;
}

// constant function to determine whether current_item is valid
bool sequenceFixed::is_item() const {
	return (current_index < used);
}


// constant function to return the current item
// preconditon: is_item() returns true
// postcondition: item at current_index is returned
sequenceFixed::value_type sequenceFixed::current() const {
	// ensure that current_index is value
	assert(is_item());
	return data[current_index];
}

// function to set current_index to beginning of sequenceFixed
// postcondition: first item on sequenceFixed becomes the current item
void sequenceFixed::start() {
	current_index = 0;
}

// function to advance current_index to next item in sequenceFixed
// precondition: is_item() returns true
// postcondition: if current_index was already last item, there is no longer any current_item
void sequenceFixed::advance() {
	assert(is_item());
	current_index++;
}

// function to insert new value before current
// if current item not valid, insert at beginning otherwise move items over and new item is current
// precondition: size() < CAPACITY
// postcondition: copy of item has been inserted
void sequenceFixed::insert(const value_type& entry) {
	// ensure available space
	assert(size() < CAPACITY);
	// if no current, place at front
	if (!is_item())
		current_index = 0;
	// starting at end move items over to make room for entry
	for (size_type i = used; i > current_index; i--)
		data[i] = data[i - 1];
	// place item in data
	data[current_index] = entry;
	// increment number of items used
	used++;
}

// function to attach item after current
// precondition: size() < CAPACITY
// postcondition: copy of item has been attached
void sequenceFixed::attach(const value_type& entry) {
	// ensure available space
	assert(size() < CAPACITY);
	// if no current, place at end
	if (!is_item()) 
		current_index = used - 1;
	// goes through data to find the end and make room for the new value
	for (size_type i = used; i > current_index; i--)
		data[i] = data[i - 1];
	// place value behind the current index
	data[current_index + 1] = entry;
	// make the new value the current index
	current_index += 1;
	// increment number of items used
	used++;
}

// precondition: is_item returns true
// postcondition: the current item is removed, and the item after is the new current(if possible)
void sequenceFixed::remove_current() {
	// ensure that something is in the sequence
	assert(is_item());
	// subtracting from used to make the sequence one value smaller so the loop will work correctly...
	// in the case that there is only one value currently, the function will break out and
	// not enter the for loop and there will be no current value
	used -= 1;
	// overwrite the data into the old current index and beyond
	for (size_type i = current_index; i < used; i++) {
		data[i] = data[i + 1];
	}
}

// precondition: size() > 0
// postcondition: deletes one copy of value in sequence. sets current_index to first index.
// returns true if value was found and deleted. false if not found.
bool sequenceFixed::erase_one(const value_type& entry) {
	// ensure that the sequence has at least one value in it
	assert(size() > 0);
	// go through the entire sequence
	for (size_type i = 0; i < used; i++) {
		// if the entry is equal to the first found value in the sequence then...
		if (entry == data[i]) {
			// checking to see if there are more than one options
			if (size() > 1) {
				// decrement used to not have out of bounds values
				--used;
				// noted that it's found. go ahead and keep going through sequence...
				for (size_type j = i; j < used; j++) {
					// overwrite data
					data[j] = data[j + 1];
				}
				// if theres more values leftover, set the first item in the sequence to current_index
				current_index = 0;
				return true;
			}
			// in the case that there was only one value and we used the erase_one function...
			if (size() == 1) {
				// made the sequence one value smaller and return no current value
				used -= 1;
				// set the current_index to 0 just to meet the homework requirements
				current_index = 0;
				return true;
			}
			
		}
	}
	// the value the user tried to delete isn't in the sequence, however, we still set the first
	// item in the sequence to the current_index
	current_index = 0;
	return false;
}

/*
==========>TEST RESULTS<==========
If you submit the Chapter 3 sequenceFixed class now, you will have
30 points out of the 30 points from this test program.
==========>POINT SUMMARY<==========
Testing insert, attach, and the constant member functions
POINTS = 7 out of 7
Testing situations where the cursor goes off the sequenceFixed when using attach and remove_current member functions
POINTS = 6 out of 6
Testing remove_current member function
POINTS = 7 out of 7
Testing erase_one member function
POINTS = 10 out of 10
Press any key to continue . . .
*/