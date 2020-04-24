// FILE: stackArray.h 
// TEMPLATE CLASS PROVIDED: stackArray<Item>
//
// TEMPLATE PARAMETER, ALIASES and MEMBER CONSTANTS for the stackArray<Item> class:
//   The template parameter, Item, is the data type of the items in the stackArray,
//   also defined as stackArray<Item>::value_type. It may be any of the C++ built-in
//   types (int, char, etc.), or a class with a default constructor, a copy
//   constructor, and an assignment operator. The definition
//   stackArray<Item>::size_type is the data type of any variable that keeps track of
//   how many items are in a stackArray. The static const CAPACITY is the
//   maximum capacity of a stackArray for this first stackArray implementation.
// NOTE:
//   Many compilers require the use of the new keyword typename before using
//   the expressions stackArray<Item>::value_type and stackArray<Item>::size_type.
//   Otherwise the compiler doesn't have enough information to realize that it
//   is the name of a data type.
//
//  VALUE SEMANTICS for the stackArray<Item> class:
//     Assignments and the copy constructor may be used with stackArray<Item> 
//     objects.
//
// INVARIANT for the stackArray class:
//   1. The number of items in the stackArray is in the member variable used.
//   2. The actual items of the stackArray are stored in a partially-filled
//      array data[0]..data[used-1]. The stackArray elements appear from the
//      bo

#ifndef MAIN_SAVITCH_stackArray_H
#define MAIN_SAVITCH_stackArray_H
#include <cstdlib>  // Provides size_t
#include <cassert>  // Provides assert

template <class Item>
class stackArray
{
public:
	// ALIASES AND MEMBER CONSTANT 
	using size_type = std::size_t;
	using value_type = Item;
	static const size_type CAPACITY = 30;
	
	// CONSTRUCTOR
	//   stackArray( )
	//     Postcondition: The stackArray has been initialized as an empty stackArray.
	//
	stackArray() { used = 0; }
	
	// CONSTANT MEMBER FUNCTIONS
	//   bool empty( ) const
	//     Postcondition: Return value is true if the stackArray is empty.
	//
	bool empty() const { return (used == 0); }
	//   size_type size( ) const
	//     Postcondition: Return value is the total number of items in the stackArray.
	//
	size_type size() const { return used; }
	Item top() const;
	
	// MODIFICATION MEMBER FUNCTIONS
	void push(const Item& entry);
	void pop();

private:
	Item data[CAPACITY];        // Partially filled array 
	size_type used;             // How much of array is being used
};

//   Item top( ) const
//     Precondition: size( ) > 0.
//     Postcondition: The return value is the top item of the stackArray (but the
//     stackArray is unchanged. This differs slightly from the STL stackArray (where
//     the top function returns a reference to the item on top of the stackArray).
//
template <class Item>
Item stackArray<Item>::top() const
// Library facilities used: cassert
{
	assert(!empty());
	return data[used - 1];
}

template <class Item>
const typename stackArray<Item>::size_type stackArray<Item>::CAPACITY;

//   void push(const Item& entry)
//     Precondition: size( ) < CAPACITY.
//     Postcondition: A new copy of entry has been pushed onto the stackArray.
//
template <class Item>
void stackArray<Item>::push(const Item& entry)
// Library facilities used: cassert
{
	assert(size() < CAPACITY);
	data[used] = entry;
	++used;
}

//   void pop( )
//     Precondition: size( ) > 0.
//     Postcondition: The top item of the stackArray has been removed.
//
template <class Item>
void stackArray<Item>::pop()
// Library facilities used: cassert
{
	assert(!empty());
	--used;
}
#endif

