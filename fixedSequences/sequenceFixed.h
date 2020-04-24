#pragma once
/*
	Author: Jameson O'Malley
	Date: 09/12/2018
	File: sequenceFixed.h
	Desc: Specification file for the sequenceFixed class
*/
#include <cstdlib>
class sequenceFixed {

public:
	// aliases for 'dynamic' data types
	using value_type = double;
	using size_type = std::size_t;
	// maximum size of container
	static const size_type CAPACITY = 30;
	// default constructor
	sequenceFixed();
	// constant member function
	size_type size() const;
	bool is_item() const;
	value_type current() const;
	// functions to position current_index
	void start();
	void advance();
	// functions to modify stored data
	void insert(const value_type&);
	void attach(const value_type&);
	void remove_current();
	bool erase_one(const value_type&);
private:
	value_type data[CAPACITY]; // relevant items stored in data[0] to data[used-1]
	size_type used; // number of items stored
	size_type current_index; // current item's index reference
};