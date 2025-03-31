#pragma once
#include <algorithm>
#include <cstdlib>
// #include <format>
#include <initializer_list>
#include <stdexcept>

namespace dev {

template<class T>
class vector {
private:
    class m_iterator_type;
public:
    using iterator = m_iterator_type;
    using const_iterator = const iterator;

    ~vector();
    vector(); // Default construction
    vector(vector& other); // Copy construction
    vector(vector&& other); // Move construction
    vector& operator=(vector& other); // Copy assignment
    vector& operator=(vector&& other); // Move assignment
    vector(size_t count, T value = T()); // Fill Construction
    vector(std::initializer_list<T> list);
    vector& operator=(std::initializer_list<T> list);

    // Access
    T& at(size_t index) const;
    T& operator[](size_t index) const;
    T& front() const;
    T& back() const;
    T* data() const;

    // Iterators
    iterator begin() const;
    const_iterator cbegin() const;
    iterator end() const;
    const_iterator cend() const;

    // Capacity
    bool empty() const;
    size_t size() const;
    void reserve(size_t space);
    size_t capacity() const;

    // Modification
    void clear();
    iterator insert(const_iterator location, const T& value);
    iterator erase(const_iterator location);
    void push_back(const T& value);
    void pop_back();
private:
    class m_iterator_type;

    T* m_arr_ptr;
    size_t m_size;
    size_t m_capacity;

    void m_copy_from_initalizer_list(std::initializer_list<T> list);
    void m_copy_from_other(vector& from);
    void m_move_from_other(vector& from);
    void m_malloc_internal_array(size_t new_capacity);
    void m_realloc_internal_array(size_t capacity);
};

template<typename T>
class vector<T>::m_iterator_type {
public:
    T* operator->();
    T& operator*();
    m_iterator_type operator+(int n) const;
    m_iterator_type operator-(int n) const;
    m_iterator_type& operator+=(int n);
    m_iterator_type& operator-=(int n);
    m_iterator_type& operator++();
    m_iterator_type& operator--();
    m_iterator_type operator++(int);
    m_iterator_type operator--(int);
private:
    friend class vector;
    T* m_internal_pointer;
    m_iterator_type(T*);
};
template<class T>
void vector<T>::m_copy_from_initalizer_list(std::initializer_list<T> list) {
    m_size = list.size();
    m_malloc_internal_array(m_size);
    std::copy(list.begin(), list.end(), m_arr_ptr);
}

/** Copies the data of `to` to `from`
 * 
 */
template<class T>
void vector<T>::m_copy_from_other(vector& other) {
    if (this == &other) {
        return;
    }
    
    // Copy data
    this->m_arr_ptr = new T[other.m_capacity];
    std::copy(other.m_arr_ptr, other.m_arr_ptr + other.m_size, this->m_arr_ptr); 
    
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
}

/** Moves the data of `*this` to `from`
 * This function does not literally "move" the data, but swaps 
 * the internal pointers of the Vectors and sets the old data's internal pointer to null;
 */
template<class T>
void vector<T>::m_move_from_other(vector& other) {
    if (this == &other) {
        return;
    }
    
    // Move data (change pointers)
    this->m_arr_ptr = other.m_arr_ptr;
    other.m_arr_ptr = nullptr;
    
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;
}

template<class T>
void vector<T>::m_malloc_internal_array(size_t new_capacity) {
    m_arr_ptr = new T[new_capacity]; // create new memory
    m_capacity = new_capacity; // set capacity to new capacity
}

// Set the memory to a new capacity. Can increase and reduce memory.
template<class T>
void vector<T>::m_realloc_internal_array(size_t new_capacity) {
    if (new_capacity > m_capacity) {
        T* new_ptr = new T[new_capacity]; // create new memory
        std::copy(m_arr_ptr, m_arr_ptr + m_capacity, new_ptr); // copy old memory to new memory
        delete[] m_arr_ptr; // deallocate old memory
        m_arr_ptr = new_ptr; // assign internal pointer to new memory
        m_capacity = new_capacity; // set capacity to new capacity
    }
}

// Destructor
template<class T>
vector<T>::~vector() {
    if (m_arr_ptr != nullptr) {
        delete[] m_arr_ptr;
    }
}

template<class T>
vector<T>::vector() {
    m_size = 0;
    m_malloc_internal_array(3);
}

// Copy constructor
template<class T>
vector<T>::vector(vector& other) {
    m_copy_from_other(other); 
}

// Move constructor
template<class T>
vector<T>::vector(vector&& other) {
    m_move_from_other(other);
}

// Copy assignment
template<class T>
vector<T>& vector<T>::operator=(vector& other) {
    m_copy_from_other(other);
    return *this; 
}

// Move assignment
template<class T>
vector<T>& vector<T>::operator=(vector&& other) {
    m_move_from_other(other); 
    return *this;
}

// Construct from size and value
template<class T>
vector<T>::vector(size_t count, T value) {
    m_size = count;
    m_capacity = count;
    m_arr_ptr = new T[m_capacity];
    std::fill(m_arr_ptr, m_arr_ptr + m_size, value);
}

template<class T>
vector<T>::vector(std::initializer_list<T> list) {
    m_copy_from_initalizer_list(list);
}

template<class T>
vector<T>& vector<T>::operator=(std::initializer_list<T> list) {
    m_copy_from_initalizer_list(list);
    return *this;
}

// Access
template<class T>
T& vector<T>::at(size_t index) const {
    if (index >= m_size) {
        throw std::out_of_range(std::format("Error: Tried to index vector at {} when size is {}", index, m_size));
    }

    return m_arr_ptr[index];
}

template<class T>
T& vector<T>::operator[](size_t index) const {
    return m_arr_ptr[index];
}

template<class T>
T& vector<T>::front() const {
    return m_arr_ptr[0];
}

template<class T>
T& vector<T>::back() const {
    return m_arr_ptr[m_size - 1];
}

template<class T>
T* vector<T>::data() const {
    return m_arr_ptr;
}

// Iterators
template<typename T>
typename vector<T>::iterator vector<T>::begin() const {
    return m_arr_ptr;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const {
    return m_arr_ptr;
}

template<typename T>
typename vector<T>::iterator vector<T>::end() const {
    return m_arr_ptr + m_size;
}

template<typename T>
typename vector<T>::const_iterator vector<T>::cend() const {
    return m_arr_ptr + m_size;
}

// Capacity
template<class T>
bool vector<T>::empty() const {
    return m_size == 0;
}

template<class T>
size_t vector<T>::size() const {
    return m_size;
}

template<class T>
void vector<T>::reserve(size_t capacity) {
    if (capacity > m_capacity) {
        m_realloc_internal_array(capacity);
    }
}

template<class T>
size_t vector<T>::capacity() const {
    return m_capacity;
}

// Modification
template<typename T>
void vector<T>::clear() {
    m_size = 0;
}

template<typename T>
typename vector<T>::iterator vector<T>::insert(typename vector<T>::const_iterator location, const T& value) {
    int difference_from_start_to_index = location.m_internal_pointer - m_arr_ptr;

    if (m_size >= m_capacity) {
        m_realloc_internal_array(m_capacity * 1.5);
    }

    // Move data from [`index`, `m_size`) to [`index + 1`, `m_size + 1`)
    T* start_ptr = m_arr_ptr + difference_from_start_to_index;
    std::copy_backward(start_ptr, m_arr_ptr + m_size - 1, start_ptr + 1);
    *start_ptr = value;
    ++m_size;
    return start_ptr;
}

template<typename T>
typename vector<T>::iterator vector<T>::erase(typename vector<T>::const_iterator location) {
    T* start_ptr = location.m_internal_pointer + 1;
    std::copy(start_ptr, start_ptr + m_size, location);
    --m_size;
    return location;
}

template<typename T>
void vector<T>::push_back(const T& value) {
    if (m_size >= m_capacity) {
        m_realloc_internal_array(m_capacity * 1.5);
    }
    
    m_arr_ptr[m_size] = value;
    ++m_size;
}

template<typename T>
void vector<T>::pop_back() {
    --m_size;
}

template<typename T>
T* vector<T>::m_iterator_type::operator->() {
    return m_internal_pointer;
}

template<typename T>
T& vector<T>::m_iterator_type::operator*() {
    return *m_internal_pointer;
}

template<typename T>
typename vector<T>::m_iterator_type vector<T>::m_iterator_type::operator+(int n) const {
    m_iterator_type it = *this;
    it.m_internal_pointer += n;
    return it;
}

template<typename T>
typename vector<T>::m_iterator_type vector<T>::m_iterator_type::operator-(int n) const {
    m_iterator_type it = *this;
    it.m_internal_pointer -= n;
    return it;
}

template<typename T>
typename vector<T>::m_iterator_type& vector<T>::m_iterator_type::operator+=(int n) {
    m_internal_pointer += n;
    return *this;
}

template<typename T>
typename vector<T>::m_iterator_type& vector<T>::m_iterator_type::operator-=(int n) {
    m_internal_pointer -= n;
    return *this;
}

template<typename T>
typename vector<T>::m_iterator_type& vector<T>::m_iterator_type::operator++() {
    ++m_internal_pointer;
    return *this;
}

template<typename T>
typename vector<T>::m_iterator_type& vector<T>::m_iterator_type::operator--() {
    --m_internal_pointer;
    return *this;
}

template<typename T>
typename vector<T>::m_iterator_type vector<T>::m_iterator_type::operator++(int) {
    m_iterator_type it = *this;
    ++m_internal_pointer;
    return it;
}

template<typename T>
typename vector<T>::m_iterator_type vector<T>::m_iterator_type::operator--(int) {
    m_iterator_type it = *this;
    --m_internal_pointer;
    return it;
}

template<typename T>
vector<T>::m_iterator_type::m_iterator_type(T* source_ptr) : m_internal_pointer{source_ptr} {
    
}

};