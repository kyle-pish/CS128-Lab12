// Author: Brian Law

#ifndef RECURSIVE_LINKED_LIST_H_
#define RECURSIVE_LINKED_LIST_H_

#include <string>

// A recursive linked list class. 
class RecursiveLinkedList {
  public:
    RecursiveLinkedList(std::string new_data);
    ~RecursiveLinkedList();

    // Provided to you
    void Append(std::string new_string);
    std::string Get(int index);
    std::string ToString();

    // To be completed by you
		int GetSize();
    int Count(std::string count_me);
    void Set(std::string new_string, int index);
		int IndexOf(std::string index_me);
    void Insert(std::string new_string, int index);
    std::string Pop();
    std::string Pop(int index);

    std::string data_;              // This is the actual data element stored in this RLL
    RecursiveLinkedList* next_;     // This is a pointer to the inner RLL within this RLL
};

#endif