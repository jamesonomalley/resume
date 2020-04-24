// FILE: pQueueList.h
// CLASS PROVIDED: PriorityQueue<Item> (a priority queue of items)
//
// VALUE SEMANTICS for the PriorityQueue class:
//   Assignments and the copy constructor may be used with
//   PriorityQueue objects

#ifndef pQueueList_H
#define pQueueList_H
#include <cstdlib> // Provides size_t
#include <cassert> // Provides assert

// template PNode for a linked list with priority
template <class Item>
struct PNode {
	Item data;
	unsigned int priority;
	PNode *link;
};

// Invariant of the PriorityQueue class:
//    head_ptr is the head pointer for a linked list that
//    contains the items along with their priorities. These PNodes are
//    kept in order from highest priority (at the head of the list)
//    to lowest priority (at the tail of the list). The private member
//    variable, many_nodes, indicates how many nodes are on the list.
//    The data type PNode is completely defined above.
//
template <class Item>
class PriorityQueue {
public:

	// CONSTRUCTORS and DESTRUCTOR
	PriorityQueue();
	PriorityQueue(const PriorityQueue<Item>& source);
	~PriorityQueue();

	// CONSTANT MEMBER FUNCTIONS
	//   bool is_empty( ) const
	//     Postcondition: Return value is true if the PriorityQueue is empty.
	//
	bool is_empty() const { return many_nodes == 0; }

	//   size_t size( ) const
	//     Postcondition: Return value is the total number of items in the
	//     PriorityQueue.
	//
	size_t size() const { return many_nodes; }

	// MODIFICATION MEMBER FUNCTIONS	
	void insert(const Item& entry, unsigned int priority);
	Item get_front();
	void operator =(const PriorityQueue<Item>& source);

private:
	// Note: head_ptr is the head pointer for a linked list that
	// contains the items along with their priorities. These PNodes are
	// kept in order from highest priority (at the head of the list)
	// to lowest priority (at the tail of the list). The private member
	// variable, many_nodes, indicates how many nodes are on the list.
	// The data type PNode is completely defined above.
	PNode<Item>* head_ptr;
	size_t many_nodes;
};

//   PriorityQueue( )
//     Postcondition: The PriorityQueue has been initialized with no Items.
//
template <class Item>
PriorityQueue<Item>::PriorityQueue() {
	many_nodes = 0;
	head_ptr = nullptr;
}

//   PriorityQueue(const PriorityQueue& source)
//     Postcondition: The PriorityQueue has been initialized with a copy of the
//     passed PriorityQueue parameter.
//
template <class Item>
PriorityQueue<Item>::PriorityQueue(const PriorityQueue<Item>& source) {
	PNode<Item> *source_cursor; // To traverse the source list.
	PNode<Item> *my_cursor; // To construct my own list.

	// Handle the special case of an empty list:
	many_nodes = 0;
	head_ptr = nullptr;
	if (source.many_nodes == 0)
		return;

	// Insert the first PNode into this new list.
	insert(source.head_ptr->data, source.head_ptr->priority);
	many_nodes = 1;

	// Traverse the source list,
	// adding copies of each PNode that's encountered:
	my_cursor = head_ptr;
	source_cursor = source.head_ptr->link;
	while (source_cursor != nullptr)
	{
		my_cursor->link = new PNode<Item>;
		my_cursor = my_cursor->link;
		my_cursor->data = source_cursor->data;
		my_cursor->priority = source_cursor->priority;
		my_cursor->link = nullptr;
		source_cursor = source_cursor->link;
	}
	many_nodes = source.many_nodes;
}

//   ~PriorityQueue()
//     Postcondition: All items have been removed from the PriorityQueue.
//
template <class Item>
PriorityQueue<Item>::~PriorityQueue() {
	PNode<Item> *temp;

	while (head_ptr != nullptr)
	{
		temp = head_ptr;
		head_ptr = head_ptr->link;
		delete temp;
	}
}

//   void insert(const Item& entry, unsigned int priority)
//     Postcondition: A new copy of entry has been inserted with the specified
//     priority.
//
template <class Item>
void PriorityQueue<Item>::insert(const Item& entry, unsigned int priority) {
	PNode<Item> *insert_ptr;  // PNode for the new element
	PNode<Item> *temp_ptr; // PNode for new temp element
	// Create the new PNode
	insert_ptr = new PNode<Item>;
	insert_ptr->data = entry;
	insert_ptr->priority = priority;
	// **INSERT AT PROPER LOCATION IN QUEUE LINKED LIST**
	if (is_empty()) {
		insert_ptr->link = head_ptr;
		head_ptr = insert_ptr;
	}
	else if (priority > head_ptr->priority) {
		head_ptr->link = insert_ptr;
		head_ptr = insert_ptr;
	}
	else {
		temp_ptr = insert_ptr;
		while (temp_ptr->link != NULL && temp_ptr->priority <= priority) {
			temp_ptr = temp_ptr->link;
		}
		insert_ptr = temp_ptr;
		temp_ptr->link = insert_ptr;
	}
	// Increment number of nodes
	many_nodes++;
}

//   Item get_front( )
//     Precondition: size( ) > 0.
//     Postcondition: The highest priority item has been returned and has been
//     removed from the PriorityQueue. (If several items have equal priority,
//     then the one that entered first will come out first.)
//
template <class Item>
Item PriorityQueue<Item>::get_front() {
	Item answer;
	PNode<Item> *temp;

	assert(size() > 0);
	answer = head_ptr->data;
	temp = head_ptr;
	head_ptr = head_ptr->link;
	delete temp;
	many_nodes--;
	return answer;
}

//   operator = (const PriorityQueue& source)
//     Postcondition: The existing PriorityQueue has been set to a copy of the
//     passed PriorityQueue parameter.
//
template <class Item>
void PriorityQueue<Item>::operator =(const PriorityQueue<Item>& source) {
	PNode<Item> *source_cursor; // To traverse the source list.
	PNode<Item> *my_cursor; // To construct my own list.

	// Handle self-assignment.
	if (this == &source)
		return;

	// Release the old memory:
	while (many_nodes > 0)
		get_front();

	// Handle the special case of an empty list:
	if (source.many_nodes == 0)
		return;

	// Insert the first PNode into this new list.
	insert(source.head_ptr->data, source.head_ptr->priority);
	many_nodes = 1;

	// Traverse the source list,
	// adding copies of each PNode that's encountered:
	my_cursor = head_ptr;
	source_cursor = source.head_ptr->link;
	while (source_cursor != nullptr)
	{
		my_cursor->link = new PNode<Item>;
		my_cursor = my_cursor->link;
		my_cursor->data = source_cursor->data;
		my_cursor->priority = source_cursor->priority;
		my_cursor->link = nullptr;
		source_cursor = source_cursor->link;
	}
	many_nodes = source.many_nodes;
}

#endif
