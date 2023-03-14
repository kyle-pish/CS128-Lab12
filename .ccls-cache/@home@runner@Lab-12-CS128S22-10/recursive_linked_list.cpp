// Author: Brian Law

//Kyle Pish & Josh Reed
//4/7/2022

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
  if (RecursiveLinkedList::next_ != 0) {
    return 1 + RecursiveLinkedList::next_->GetSize(); //Counts every element by adding 1 for every function call, and then stopping once it gets to the end
  }
  else {
    return 1; //Counts the last element
  }
}

// Recursive method to return the number of times this element occurs in this linked list.
int RecursiveLinkedList::Count(std::string count_me) {

  //This setup just checks if the current element is what we're counting; if it is, then return 1 + itself called on the next element, ultimately stopping at the last element.
  if (RecursiveLinkedList::data_ == count_me) {
    if (RecursiveLinkedList::next_ != 0) { 
      return (1 + RecursiveLinkedList::next_->Count(count_me)); //If a given element is what we're looking for, and there is another element, we add one to our "count" and call the next element
    } 

    else {
      return 1; //If it's what we're looking for but it *is* the last element, we count it and end the recursion
    }
  }

  if (RecursiveLinkedList::data_ != count_me) {
    if (RecursiveLinkedList::next_ != 0) {
      return RecursiveLinkedList::next_->Count(count_me); //If it isn't what we're counting, we simply call the next element (if there is one)
    }

    else {
      return 0; //Ends the recursion
    }
  }
}

// Recursive method to set the element at the specified index in this linked list to the specified value.
void RecursiveLinkedList::Set(std::string new_string, int index) {
  //Functionally, this is almost identical to "Get", but instead of having to return a value up, we're just replacing it with new_string.
  
  if (index == 0) {
		RecursiveLinkedList::data_ = new_string;
	}
    
	// Error case: if the index is too big and we've reached the end of the LL, abort.
  else if (RecursiveLinkedList::next_ == 0) {
    throw std::runtime_error("Error: Cannot get index that does not exist.");
  }
  else {
    // Recursive case: Recursively get on the smaller, internal linked list, but with index - 1, because
    // the i-th element of this linked list is the i-1-th element of the internal linked list.
    RecursiveLinkedList::next_->Set(new_string, index - 1);
  }
}

// Recursive method to find the index of the first instance of index_me in this linked list.
int RecursiveLinkedList::IndexOf(std::string index_me) {

  if (RecursiveLinkedList::data_ == index_me) {
    return 0;
  }

  else if (RecursiveLinkedList::next_ == 0) {
    return -1;
  }

  int RecursiveOutput = RecursiveLinkedList::next_->IndexOf(index_me);

  if (RecursiveOutput != -1) {
    return 1 + RecursiveOutput; //This is a bit bizarre, but essentially the output of the recursive call is the condition. It'll keep being called until it reaches either the element, or the end.
    //If it reaches the element, it will return 0, this if-statement will cause it to add one to each return until we add up to the correct index.
  }

  else {
    return -1; //If it reaches the end, it will return -1, and then continue to return -1 all the way back up
  }
}

// Recursive method to insert the specified value into this linked list at the specified index.
void RecursiveLinkedList::Insert(std::string new_string, int index) {
  //Again, this is functionally very similar to set, but instead, we stop one before the index and insert rather than changing existing data
  
  if (index == 1) { //Stopping one before the index and performing the actual insert, storing the next element and setting it as the new element's next_
    RecursiveLinkedList* after_insert = RecursiveLinkedList::next_;
    RecursiveLinkedList::next_ = new RecursiveLinkedList(new_string);
    RecursiveLinkedList::next_->next_ = after_insert;
  }

  // Error case: if the index is too big and we've reached the end of the LL, abort.
  else if (RecursiveLinkedList::next_ == 0) {
    throw std::runtime_error("Error: Cannot get index that does not exist.");
  }
  else {
    // Recursive case: Recursively get on the smaller, internal linked list, but with index - 1, because
    // the i-th element of this linked list is the i-1-th element of the internal linked list.
    RecursiveLinkedList::next_->Insert(new_string, index - 1);
  }
}


// Recursive method to remove and return the element at the end of this linked list.
std::string RecursiveLinkedList::Pop() {
  //Like several others, this just moves to the end with recursive calls checking for the null pointer. 
  
  if (RecursiveLinkedList::next_->next_ == 0) { //If the next element is the last, save its data and remove it
    std::string output = RecursiveLinkedList::next_->data_;
    delete RecursiveLinkedList::next_;
    RecursiveLinkedList::next_ = 0;

    return output;
  }

  else { //If there is more of the list to go, recursive call moves forward
    return RecursiveLinkedList::next_->Pop();
  }
  
}

// Recursive method to remove and return the element at the specified index.
std::string RecursiveLinkedList::Pop(int index) {
  //Again, this is functionally very similar to set, but instead, we stop one before the index and insert rather than changing existing data
  
  if (index == 1) { //Stopping one before the index, storing the next element and setting it as the previous element's next_
    std::string output = RecursiveLinkedList::next_->data_;
    RecursiveLinkedList* after_pop = RecursiveLinkedList::next_->next_;
    RecursiveLinkedList::next_->next_ = 0; //Nulling the element being popped's next pointer so the destructor doesn't get overexcited and delete everything
    delete RecursiveLinkedList::next_;
    RecursiveLinkedList::next_ = after_pop;

    return output;
  }

  // Error case: if the index is too big and we've reached the end of the LL, abort.
  else if (RecursiveLinkedList::next_ == 0) {
    throw std::runtime_error("Error: Cannot get index that does not exist.");
  }
  else {
    // Recursive case: Recursively get on the smaller, internal linked list, but with index - 1, because
    // the i-th element of this linked list is the i-1-th element of the internal linked list.
    return RecursiveLinkedList::next_->Pop(index - 1);
  }
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