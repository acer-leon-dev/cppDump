#include "circular_list.hpp"
#include <cstdlib>
#include <cstddef>
#include <functional>
#include <iostream>
#include <sstream>

// DEBUG
template <typename T> void* single_node<T>::operator new(size_t size) {
    std::cout << "Allocated " << size << " bytes for a node" << std::endl;
    void* ptr = malloc(size);
    return ptr;
}

// DEBUG
template <typename T> void single_node<T>::operator delete(void* ptr) {
    std::cout << "Freed " << sizeof(*(single_node*)ptr) << " bytes for a node" << std::endl;
    free(ptr);
}

template <typename T> circular_list<T>::circular_list() {
    // Set head pointer and cursor to null
    this->head = nullptr;
    this->cursor = nullptr;
}

template <typename T> circular_list<T>::circular_list(const circular_list& other) {
    single_node<T>* other_n = other.head;
    single_node<T>* this_n = new single_node<T>;
    this->head = this_n;
    this->cursor = this->head;
    while (1) {
        if (other_n == other.cursor) {
            this->cursor = this_n;
        }
        this_n->value = other_n->value;
        other_n = other_n->next;
        if (other_n == other.head) {
            this_n->next = this->head;
            return;
        }
        this_n->next = new single_node<T>;
        this_n = this_n->next;
    }
}

template <typename T> circular_list<T>::~circular_list() {
    if (this->empty()) {
        std::cout << "Deleted list" << std::endl; // DEBUG
        std::cout << *this << std::endl; // DEBUG
        return;
    }

    // Recursively deletes all the nodes in the list, starting from a given first node
    std::function<void(single_node<T>*)> _delete_node_sequence = [&](single_node<T>* current) -> void {
        if (current->next == this->head) { // Stop recursion at last node
            delete current;
            return;
        }
        _delete_node_sequence(current->next); // Recurse to next node
        delete current; // Delete current node after the recursive call
        };

    _delete_node_sequence(this->head->next); // Start from second node, then
    delete this->head; // delete first node

    // Set head and cursor to null
    this->head = nullptr;
    this->cursor = nullptr;
    std::cout << "Deleted list" << std::endl; // DEBUG
}

template <typename T> bool circular_list<T>::empty() const {
    return this->head == nullptr && this->cursor == nullptr;
}

template <typename T> bool circular_list<T>::at_start() const {
    return this->cursor == this->head;
}

template <typename T> bool circular_list<T>::at_end() const {
    return this->cursor->next == head;
}

template <typename T> T& circular_list<T>::front() const {
    return this->head->value;
}

template <typename T> T& circular_list<T>::back() const {
    // Iterate from start to end node
    single_node<T>* i_n = this->head;
    do {
        i_n = i_n->next;
    } while (i_n->next != this->head);
    return i_n->value;
}

template <typename T> void circular_list<T>::next() {
    if (this->empty()) {
        std::cout << "Did not move to next node" << std::endl; // DEBUG
        std::cout << "List: " << *this << std::endl; // DEBUG
        return;
    }
    this->cursor = this->cursor->next;
    std::cout << "Moved to next node" << std::endl; // DEBUG
    std::cout << "List: " << *this << std::endl; // DEBUG
}

template <typename T> void circular_list<T>::prev() {
    cursor = _get_node_before_cursor();
    std::cout << "Moved to previous node" << std::endl; // DEBUG
    std::cout << "List: " << *this << std::endl; // DEBUG
}

template <typename T> T circular_list<T>::get() const {
    return cursor->value;
}

template <typename T> void circular_list<T>::set(T value) {
    cursor->value = value;
}

template <typename T> void circular_list<T>::insert(T value) {
    single_node<T>* p_new_node = new single_node<T>; // Create pointer to new node
    p_new_node->value = value;
    // If list is empty:
    if (this->empty()) {
        this->head = p_new_node;
        this->cursor = p_new_node;
        p_new_node->next = p_new_node;
        std::cout << "Added " << value << " as the only node" << std::endl; // DEBUG
    }
    // If cursor is at the last node:
    else if (this->at_end()) {
        cursor->next = p_new_node;
        p_new_node->next = this->head;
        std::cout << "Added " << value << " as the last node" << std::endl; // DEBUG
    }
    else {
        p_new_node->next = cursor->next;
        cursor->next = p_new_node;

        // DEBUG
        std::cout << "Added " << value;
        if (p_new_node->next == p_new_node) {
            std::cout << " as the first node";
        }
        else {
            std::cout << " as a middle node";
        }
        std::cout << std::endl;

    }
    std::cout << "List: " << *this << std::endl; // DEBUG
}

template <typename T> void circular_list<T>::remove() {
    if (this->empty()) {
        std::cout << "Removed nothing" << std::endl; // DEBUG
        std::cout << "List: " << *this << std::endl; // DEBUG
        return;
    }

    single_node<T>* previous_node = _get_node_before_cursor(); // Get the node before cursor
    previous_node->next = this->cursor->next;

    delete this->cursor; // Delete node at cursor then move cursor to the previous node
    cursor = previous_node;
    std::cout << "Removed " << this->cursor->value << std::endl; // DEBUG
    std::cout << "List: " << *this << std::endl; // DEBUG
}

template <typename T> std::ostream& operator << (std::ostream& out, const circular_list<T>& src) {
    if (src.empty()) {
        out << "<Empty list>";
    }
    else {
        single_node<T>* i_n = src.head;
        do {
            if (i_n == src.cursor) {
                out << '[' + std::to_string(i_n->value) + ']';
            }
            else {
                out << std::to_string(i_n->value);
            }

            if (i_n->next != src.head) {
                out << " -> ";
            }

            i_n = i_n->next;
        } while (i_n != src.head);
    }

    return out;
}

template <typename T> std::string circular_list<T>::str() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

template <typename T> single_node<T>* circular_list<T>::_get_node_before_cursor() const {
    // Set temp node to first node
    single_node<T>* i_n = this->head;
    // Iterate through each node until at the node before the cursor
    while (i_n->next != cursor) {
        i_n = i_n->next;
    }
    // Return node before cursor
    return i_n;
}
