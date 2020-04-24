// AUTHOR: Jameson O'Malley
// DATE: 10/31/2018
// FILE:  recListToolkit.h
// DESCR: 
// Recursive toolkit function for
// template based singly linked list 
// CIS2542 Lab #9.

#include "nodeTemplate.h"
#include <iostream>
using namespace std;

// recursive version to return the number
// of nodetemplates in the linked list
template <class Item>
size_t rec_list_length(const nodeTemplate<Item>* head_ptr) {
	// once head_ptr reaches nullptr, end
	if (head_ptr == nullptr) {
		return 0;
	}
	// add 1 and go on to the next nodeTemplate until you reach nullptr
	return 1 + rec_list_length(head_ptr->link());
	
}

// recursive version to return the value that points to
// the first nodeTemplate containing the specified target
// if there is no such nodeTemplate, the nullptr pointer is returned
template <class nodeTemplatePtr, class Item>
nodeTemplatePtr rec_list_search(nodeTemplatePtr head_ptr, const Item& target) {
	// if there isn't the number, end
	if (head_ptr == nullptr) {
		return nullptr;
	}
	// if the target is found, return the data
	else if (target == head_ptr->data()) {
		return head_ptr;
	}
	// recursive call to go to the next nodeTemplate, if not found already
	rec_list_search(head_ptr->link(), target);
}

// recursive version for having all nodeTemplates of the list return
// to the heap, and the head_ptr is now nullptr
template <class Item>
void rec_list_clear(nodeTemplate<Item>* head_ptr) {
	// go until head_ptr equals nullptr
	if (head_ptr != nullptr) {
		// recursive call to go to the next nodeTemplate
		rec_list_clear(head_ptr->link());
		// remove the head_ptr
		list_head_remove(head_ptr);
	}
}

// recursive version to display all items in list
template <class Item>
void rec_display_list(const nodeTemplate<Item>* head_ptr) {
	if (head_ptr != nullptr) {
		// process node
		cout << head_ptr->data() << endl;
		// recursive call with rest of list
		rec_display_list(head_ptr->link());
	}
}

// recursive version to display all items in list in reverse order
template <class Item>
void rev_display_list(const nodeTemplate<Item>* head_ptr) {
	if (head_ptr) {
		// recursive call to go to the next nodeTemplate
		rev_display_list(head_ptr->link());
		// displays data from the end and then recursively goes backwards to the front
		cout << head_ptr->data() << endl;
	}
	// exit function
	return;
}

/*
The number of items in list is 5
List items in order:
11.1
77.7
22.2
33.3
5.5
List items in reverse order:
5.5
33.3
22.2
77.7
11.1

Searching with recursive function...
Input a  value to search (0 to end): 11.1
11.1 has been found!
Input a  value to search (0 to end): 22.2
22.2 has been found!
Input a  value to search (0 to end): 5.5
5.5 has been found!
Input a  value to search (0 to end): -3.2
-3.2 has NOT been found!
Input a  value to search (0 to end): 0
Press any key to continue . . .
*/

