#ifndef _LINKED_LIST_HPP
    #define _LINKED_LIST_HPP

#include <iostream>

template<typename T> class circular_list;

template<typename T> class single_node {
public:
    // Overloaded new operator to display message upon allocation
    void* operator new(size_t size);

    // Overloaded delete operator to display message upon deletion
    void operator delete(void* ptr);
private:
    // The value stored in the node
    T value;

    // The next node pointed to by this node
    single_node<T>* next;

    // Gives linked_list access to private fields and methods
    friend class circular_list<T>;

    // Gives overloaded << operator of linked_list access to private fields and methods
    template<typename U> friend std::ostream& operator << (std::ostream& out, const circular_list<U>& l);
};

template<typename T> class circular_list {
public:
    // Constructor; Creates a new, empty linked_list
    circular_list();

    // Copy constructor; Copies from another linked_list
    circular_list(const circular_list<T>& other);

    // Destructor; Deletes the linked_list and everything in it
    ~circular_list();

    // Inserts a node with the given value after the cursor's position
    void insert(T value);

    // Removes/deletes the node at the cursor's position
    void remove();

    // Returns the value of the node at the cursor's position
    T get() const;

    // Sets the value of the node at the cursor's position
    void set(T value);

    // Moves the cursor to the next node in the list (to the start if at the end)
    void next();

    // Moves the cursor to the previous node in the list (to the end if at the start)
    void prev();

    // Returns a boolean of whether or not the list is empty
    bool empty() const;

    // Returns a boolean of whether or not cursor is at the start of the list
    bool at_start() const;

    // Returns a boolean of whether cursor or not is at the end of the list
    bool at_end() const;

    // Returns a reference to first node in the list
    T& front() const;

    // Returns a reference to the last node in the list
    T& back() const;

    // Returns the string representation of the linked list
    std::string str() const;

    // Gives overloaded << operator of linked_list access to private fields and methods
    template<typename U> friend std::ostream& operator <<(std::ostream& out, const circular_list<U>& src);

private:
    // A pointer to the first node in the linked list
    single_node<T>* head;

    // A pointer to the currently selected node in the linked list
    // Can be moved around using next() and prev()
    single_node<T>* cursor;

    // Returns a pointer to the node before cursor
    single_node<T>* _get_node_before_cursor() const;
};

// Inserts the string representation of a given linked list into a stream (and returns the stream)
template<typename T> std::ostream& operator <<(std::ostream& out, const circular_list<T>& src);

#include "circular_list.inl"

#endif // _LINKED_LIST_HPP