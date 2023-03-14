// Author: Brian Law

#include <iostream>

#include "recursive_linked_list_wrapper.h"

// Notice that for this recursive linked list, it always starts with a first element,
// rather than empty, like our regular Node-based linked lists. This isn't strictly necessary
// but makes this lab easier and more consistent with your other linked list work.
RecursiveLinkedListWrapper::RecursiveLinkedListWrapper(std::string first_string) {
  RecursiveLinkedListWrapper::head_ = new RecursiveLinkedList(first_string);
}

// Recursive delete!
RecursiveLinkedListWrapper::~RecursiveLinkedListWrapper() {
  // Do nothing if there are no elements inside.
  if (RecursiveLinkedListWrapper::head_ == 0) {
    return;
  }
  
  // Recursively delete the recursive linked lists.
  delete RecursiveLinkedListWrapper::head_;
}

// A wrapper method for the recursive Append method.
// Appends the new element at end of this linked list.
void RecursiveLinkedListWrapper::Append(std::string new_string) {
  // Handle empty linked list case with head pointer.
  if (RecursiveLinkedListWrapper::head_ == 0) {
		RecursiveLinkedListWrapper::head_ = new RecursiveLinkedList(new_string);
	}
  else {
    // Call recursive append.
		RecursiveLinkedListWrapper::head_->Append(new_string);
  }
}

// A wrapper method for the recursive Get method.
// Returns the element at the specified index inside this linked list.
std::string RecursiveLinkedListWrapper::Get(int index) {
  // If the linked list is empty, throw an error.
	if (RecursiveLinkedListWrapper::head_ == 0) {
		throw std::runtime_error("Error: Cannot get element from empty linked list.");
	}
  // Otherwise, make recursive call. (Note, no need for special head handling for this one.
  // Can you think of why? What makes Get() different than some of the other methods?)
  else {
	  return RecursiveLinkedListWrapper::head_->Get(index);
  }
}

// A wrapper method for the recursive GetSize() method.
// Returns the number of elements in this linked list.
int RecursiveLinkedListWrapper::GetSize() {
 	// If there's no head, obviously the size is 0.
	if (RecursiveLinkedListWrapper::head_ == 0) {
		return 0;
	}
  // Otherwise, recursively count how many elements there are.
  else {
	  return RecursiveLinkedListWrapper::head_->GetSize();
  }
}

// A wrapper method for the recursive Count() method.
// Returns the number of times count_me occurs in this linked list.
int RecursiveLinkedListWrapper::Count(std::string count_me) {
 	// If there's no head, obviously the element isn't in the linked list.
	if (RecursiveLinkedListWrapper::head_ == 0) {
		return 0;
	}
  // Otherwise, make a recursive call!
	else {
	  return RecursiveLinkedListWrapper::head_->Count(count_me);
  }
}

// A wrapper method for the recursive IndexOf() method.
// Returns the index of the first occurrence of index_me in the linked list, -1 if not found.
int RecursiveLinkedListWrapper::IndexOf(std::string index_me) {
	// If there's no head, obviously the element isn't in the linked list.
	if (RecursiveLinkedListWrapper::head_ == 0) {
		return -1;
	}
  // Otherwise, make a recursive call!
  else {
    return RecursiveLinkedListWrapper::head_->IndexOf(index_me);
  }
}

// A wrapper method for the recursive Set() method.
// Sets the index-th element in this linked list to the specified value.
void RecursiveLinkedListWrapper::Set(std::string value, int index) {
  // If linked list is empty...
	if (RecursiveLinkedListWrapper::head_ == 0) {
		throw std::runtime_error("Error: Cannot set elements in an empty linked list.");
	}
  // Otherwise, make recursive call. (Note, no need for special head handling for this one.
  // Can you think of why? What makes Set() different than some of the other methods?)
	else {
	  RecursiveLinkedListWrapper::head_->Set(value, index);
  }
}

// A wrapper method for the recursive Insert() method.
// Insert the specified value at the specified index in this linked list.
void RecursiveLinkedListWrapper::Insert(std::string value, int index) {
	// Because the head pointer is special, the wrapper method has to take care of the case
	// where the insertion is at the head.
	if (index == 0) {
		RecursiveLinkedList* old_head = RecursiveLinkedListWrapper::head_;
		RecursiveLinkedListWrapper::head_ = new RecursiveLinkedList(value);
		RecursiveLinkedListWrapper::head_->next_ = old_head;
	}
  // Error case: Empty linked list but trying to enter it for insertion.
	else if (RecursiveLinkedListWrapper::head_ == 0) {
		throw std::runtime_error("Error: Cannot insert at a non-zero index in an empty linked list.");
	}
  // Otherwise, make recursive call.
	else {
		RecursiveLinkedListWrapper::head_->Insert(value, index);
  }
}

// A wrapper method for the recursive Pop() method.
// Remove and return the element at the end of the linked list.
std::string RecursiveLinkedListWrapper::Pop() {
	if (RecursiveLinkedListWrapper::head_ == 0) {
		throw std::runtime_error("Error: Cannot pop from an empty linked list.");
	}

	// If the head IS the last element, the wrapper method needs to handle the popping
	// so the head pointer can be reassigned properly.
	if (RecursiveLinkedListWrapper::head_->next_ == 0) {
		std::string return_this = RecursiveLinkedListWrapper::head_->data_;
		delete RecursiveLinkedListWrapper::head_;
		RecursiveLinkedListWrapper::head_ = 0;
		return return_this;
	}
  // Otherwise, make recursive call.
  else {
    return RecursiveLinkedListWrapper::head_->Pop();
  }
}

// A wrapper method for the recursive Pop() method.
// Remove and return the element at the specified index in the linked list.
std::string RecursiveLinkedListWrapper::Pop(int index) {
	if (RecursiveLinkedListWrapper::head_ == 0) {
		throw std::runtime_error("Error: Cannot pop from an empty linked list.");
	}
	
	// In the RecursiveLinkedList class, the destructor (delete) is also recursive, so you CANNOT delete the 
  // RecursiveLinkedList and then reconnect afterwards,  because the deletion will also delete all inner 
  // RecursiveLinkedLists. You have to save a temporary pointer to the RecursiveLinkedList to be deallocated,
	// disconnect that RecursiveLinkedList from its inner RecursiveLinkedList, then deallocate the target 
  // RecursiveLinkedList, and then reconnect the linked list back together.
	if (index == 0) {
		// Save return value for later.
		std::string return_this = RecursiveLinkedListWrapper::head_->data_;

		// Save pointer to the inner linked list to assign as the new head later.
		RecursiveLinkedList* new_head = RecursiveLinkedListWrapper::head_->next_;

		// Disconnect the head element from the rest of the linked list BEFORE deleting it.
		RecursiveLinkedListWrapper::head_->next_ = 0;
		delete RecursiveLinkedListWrapper::head_;

		// Repoint to the new head element (previous inner linked list).
		RecursiveLinkedListWrapper::head_ = new_head;
		return return_this;
	}
  // Otherwise, make recursive call.
  else {
		return RecursiveLinkedListWrapper::head_->Pop(index);
  }
}

// Return a string representation of this linked list. All the std::string elements are separated by commas
// and bracketed by [].
std::string RecursiveLinkedListWrapper::ToString() {
	std::string return_this = "[";
  // If this linked list is empty, just return []
  if (RecursiveLinkedListWrapper::head_ == 0) {
	}
  else {
	  return_this += RecursiveLinkedListWrapper::head_->ToString();
  }
  return return_this + "]";
}

void RecursiveLinkedListWrapper_main() {
	RecursiveLinkedListWrapper rll1 = RecursiveLinkedListWrapper("Time");
  rll1.Append("flies");
  rll1.Append("like");
  rll1.Append("an");
  rll1.Append("arrow");

	// This output method is awful. Every time we Get, we start over from the beginning of the linked list, so with 5 calls
	// we have to (partially) traverse the linked list 4 times instead of just once. Ugh!
	std::cout << rll1.Get(0) << rll1.Get(1) << rll1.Get(2) << rll1.Get(3) << rll1.Get(4) << std::endl;

	rll1.Set("Something", 0);
  std::cout << rll1.ToString() << std::endl;

	rll1.Pop(0);
  std::cout << rll1.ToString() << std::endl;

	rll1.Insert("Fruit", 0);
  std::cout << rll1.ToString() << std::endl;

	rll1.Pop();
	std::cout << rll1.ToString() << std::endl;

	rll1.Set("a", 3);
  std::cout << rll1.ToString() << std::endl;

  rll1.Append("banana");
  std::cout << rll1.ToString() << std::endl;

  rll1.Insert("overripe", 4);
  std::cout << rll1.ToString() << std::endl;

	rll1.Set("an", 3);
  std::cout << rll1.ToString() << std::endl;
}