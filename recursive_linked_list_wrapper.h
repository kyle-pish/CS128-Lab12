// Author: Brian Law

#ifndef RECURSIVE_LINKED_LIST_WRAPPER_H_
#define RECURSIVE_LINKED_LIST_WRAPPER_H_

#include <string>

#include "recursive_linked_list.h"

// This is the wrapper class on the recursive linked list.
// These methods are NON-recursive, but will call the recursive methods
// of the RecursiveLinkedList class as needed.
class RecursiveLinkedListWrapper {
  public:
    RecursiveLinkedListWrapper(std::string first_string);
    ~RecursiveLinkedListWrapper();
    void Append(std::string new_string);
    std::string Get(int index);

		int GetSize();
    int Count(std::string count_me);
		int IndexOf(std::string index_me);
    void Set(std::string value, int index);
    void Insert(std::string value, int index);
    std::string Pop();
    std::string Pop(int index);

		std::string ToString();

  private:
    // This is the first/outer recursive linked list within the wrapper.
    RecursiveLinkedList* head_;
};

void RecursiveLinkedListWrapper_main();

#endif