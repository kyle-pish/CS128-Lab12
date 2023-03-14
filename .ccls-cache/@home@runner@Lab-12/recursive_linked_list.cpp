// Author: Brian Law

#include <iostream>
#include <stdexcept>

#include "recursive_linked_list.h"

// Create a recursive linked list with the specified data, no recursive sublist.
RecursiveLinkedList::RecursiveLinkedList(std::string new_data) {
  RecursiveLinkedList::data_ = new_data;
  RecursiveLinkedList::next_ = 0;  // This is a null pointer.
}

// Recursively deallocate all recursive sublists.
RecursiveLinkedList::~RecursiveLinkedList() {
  if (RecursiveLinkedList::next_ != 0) {
    delete RecursiveLinkedList::next_;
  }
}

// Add new_std::string to the end of this linked list.
void RecursiveLinkedList::Append(std::string new_string) {
	// Checks to see if this RLL has another RLL inside of it...
  if (RecursiveLinkedList::next_ == 0) {
		// Base case: no further recursion possible. Therefore this must be the innermost recurisve linked list.
    RecursiveLinkedList::next_ = new RecursiveLinkedList(new_string);
  }
  // Recursive case. There are more "nodes", so recurse on that smaller linked list with another Append call.
  else {
    RecursiveLinkedList::next_->Append(new_string);
  }
}

// Return the element at the specified index.
std::string RecursiveLinkedList::Get(int index) {
	// Compared to Append and the destructor (~), Get here adds two more "features" to the recursion
	// 1. Get doesn't necessarily go all the way to the innermost layer of the recursive data structure.
	// That's what the index parameter is for Get. And so as you recursively Get, you need to count down
	// the index parameter/argument so that you keep track of how far into the recursion you are.
	// 2. Get returns a value all the way out -> This means that each recursive call needs to have a
	// "return" keyword in front of it, so that the requested data gets returned all the way back up
	// each recursive step.
  
	// Base case: we've reached the index we want to fetch, so just return that element up the recursion stack.
	if (index == 0) {
		return RecursiveLinkedList::data_;
	}
	// Error case: if the index is too big and we've reached the end of the LL, abort.
  else if (RecursiveLinkedList::next_ == 0) {
    throw std::runtime_error("Error: Cannot get index that does not exist.");
  }
  else {
    // Recursive case: Recursively get on the smaller, internal linked list, but with index - 1, because
    // the i-th element of this linked list is the i-1-th element of the internal linked list.
    return RecursiveLinkedList::next_->Get(index - 1);
  }
}

// Return the number of elements in this linked list.
int RecursiveLinkedList::GetSize() {
  return 0;
}

// Recursive method to return the number of times this element occurs in this linked list.
int RecursiveLinkedList::Count(std::string count_me) {
  return 0;
}

// Recursive method to set the element at the specified index in this linked list to the specified value.
void RecursiveLinkedList::Set(std::string new_string, int index) {
}

// Recursive method to find the index of the first instance of index_me in this linked list.
int RecursiveLinkedList::IndexOf(std::string index_me) {
  return 0;
}

// Recursive method to insert the specified value into this linked list at the specified index.
void RecursiveLinkedList::Insert(std::string new_string, int index) {
}

// Recursive method to remove and return the element at the end of this linked list.
std::string RecursiveLinkedList::Pop() {
  return "";
}

// Recursive method to remove and return the element at the specified index.
std::string RecursiveLinkedList::Pop(int index) {
	return "";
}

// Recursive method to return a string representation of this linked list.
std::string RecursiveLinkedList::ToString() {
  // Base case: no inner linked list to recurse on any more, so simply return
  // our data (which is already a std::string).
	if (RecursiveLinkedList::next_ == 0) {
		return RecursiveLinkedList::data_;
	}
  // Recursive case: inner linked list exists, so recursively call ToString()
  // on it.
  else {
    // Note how we ADD the result from the recursive call to our own data. Thus
    // what will get returned ultimately will have our data PLUS the data of all
    // the linked lists nested within. Return order is "reversed," because 
    // recursive calls return in the opposite order in which they're called.
    return RecursiveLinkedList::data_ + ", " + RecursiveLinkedList::next_->ToString();
  }
}