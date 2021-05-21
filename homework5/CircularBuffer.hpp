//
// Created by Vio on 19.05.2021.
//

#ifndef PROGA5LAB_CIRCULARBUFFER_HPP
#define PROGA5LAB_CIRCULARBUFFER_HPP

#include <iostream>

template<typename T>
class Iterator {
private:
    T *ptr;
public:
    Iterator(T *pointer = nullptr)
            : ptr(pointer) {}

    using iterator_category = std::random_access_iterator_tag;
    using reference = T &;
    using pointer = T *;
    using value_type = T;
    using difference_type = int;


    bool operator!=(const Iterator &rhs) {
        return ptr != rhs.ptr;
    }

    bool operator==(const Iterator &rhs) {
        return ptr == rhs.ptr;
    }

    Iterator &operator++() {
        ptr++;
        return *this;
    }

    T &operator*() {
        return *ptr;
    }

    Iterator &operator--() {
        ptr--;
        return *this;
    }

    Iterator operator-(difference_type rhs) {
        return Iterator(ptr - rhs);
    }

    Iterator operator+(difference_type rhs) {
        return Iterator(ptr + rhs);
    }

    T &operator[](value_type value) {
        return ptr[value];
    }

    Iterator &operator+=(value_type value) {
        ptr += value;
        return *this;
    }

    Iterator &operator-=(value_type value) {
        ptr -= value;
        return *this;
    }

    difference_type operator-(Iterator &rhs) {
        return ptr - rhs.ptr;
    }

    bool operator<(Iterator &rhs) {
        return ptr < rhs.ptr;
    }

    bool operator>(Iterator &rhs) {
        return ptr > rhs.ptr;
    }

    bool operator<=(Iterator &rhs) const {
        return ptr <= rhs.ptr;
    }

    bool operator>=(Iterator &rhs) const {
        return ptr >= rhs.ptr;
    }


};

template<typename T>
class CircularBuffer {
private:
    int now_size = 0;
    int size_buffer = 0;
    T *circular_buffer;
public:

    CircularBuffer(int size = 0)
            : size_buffer(size) {
        circular_buffer = new T[size_buffer];
    }

    ~CircularBuffer() {
        delete[]circular_buffer;
    }

    T first() {
        return circular_buffer[0];
    }

    T last() {
        return circular_buffer[now_size - 1];
    }

    int get_now_size() {
        return now_size;
    }
    //todo O(1)
    void addFirst(T value) {

        for (int i = now_size; i > 0; i--) {
            circular_buffer[i] = circular_buffer[i - 1];
        }
        circular_buffer[0] = value;
        if (now_size < size_buffer) {
            now_size++;
        }
    }

    void delFirst() {
        for (int i = 0; i < now_size - 1; i++) {
            circular_buffer[i] = circular_buffer[i + 1];
        }
        now_size--;
    }

    void addLast(T value) {
        if (now_size < size_buffer) {
            circular_buffer[now_size] = value;
            now_size++;
        } else {
            for (int i = 0; i < now_size - 2; i++) {
                circular_buffer[i] = circular_buffer[i + 1];
            }
            circular_buffer[now_size - 1] = value;
        }
    }

    void delLast() {
        now_size--;
    }

    T &operator[](int x) const {
        if (x < 0 || x >= now_size) {
            std::cout << "Sorry,impossible to go by index: ";
            throw std::out_of_range("out of range");
        } else {
            return circular_buffer[x];
        }
    }

    T &operator[](int x) {
        if (x < 0 || x >= now_size) {
            //todo string into exception (size of buffer)
            std::cout << "Sorry,impossible to go by index: ";
            throw std::out_of_range("out of range");
        } else {
            return circular_buffer[x];
        }
    }

    Iterator<T> begin() const {
        return Iterator(circular_buffer);
    }

    Iterator<T> end() const {
        return Iterator(circular_buffer + now_size);
    }

    void changeCapacity(int new_size) {
        size_buffer = new_size;
        now_size = std::min(now_size, new_size);
        T *buffer = new T[new_size];
        for (int i = 0; i < now_size; i++) {
            buffer[i] = circular_buffer[i];
        }
        delete[] circular_buffer;
        circular_buffer = buffer;
        //todo memory
        delete[] buffer;

    }


};


#endif //PROGA5LAB_CIRCULARBUFFER_HPP
