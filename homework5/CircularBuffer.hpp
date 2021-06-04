//
// Created by Vio on 19.05.2021.
//

#ifndef PROGA5LAB_CIRCULARBUFFER_HPP
#define PROGA5LAB_CIRCULARBUFFER_HPP

#include <iostream>

using namespace std;

template<typename T>
class CircularBuffer;


template<typename T>
class Iterator {
private:
    T *ptr;
    T *ptr_finish;
    T *ptr_start;
    int flag;
    int now_size;
    int size_buffer;
    int flag1;
public:
    using iterator_category = std::random_access_iterator_tag;
    using reference = T &;
    using pointer = T *;
    using value_type = T;
    using difference_type = int;

    explicit Iterator(T *pointer = nullptr, T *ptr_arr_finishes = nullptr, T *ptr_arr_start = nullptr, int flags = 0,
                      difference_type now_sizes = 0, difference_type size_buffers = 0, difference_type flags1 = 0)
            : ptr(pointer), ptr_finish(ptr_arr_finishes),
              ptr_start(ptr_arr_start), flag(flags), now_size(now_sizes),
              size_buffer(size_buffers), flag1(flags1) {}


    Iterator &operator++() {
        if ((ptr + 1) > ptr_finish) {
            ptr = ptr_start;
        } else {
            ptr++;
        }
        return *this;

    }

    bool operator!=(const Iterator &rhs) {
        if ((now_size == size_buffer) && (flag == 0) && (rhs.flag == 0)) {
            flag = 1;
            if (ptr == rhs.ptr) {
                return true;
            } else {
                return ptr != rhs.ptr;
            }
        } else {
            return ptr != rhs.ptr;
        }
    }

    bool operator==(const Iterator &rhs) {
        if ((now_size == size_buffer) && (flag1 == 0) && (rhs.flag1 == 0)) {
            flag1 = 1;
            if (ptr == rhs.ptr) {
                return false;
            } else {
                return ptr == rhs.ptr;
            }
        } else {
            return ptr == rhs.ptr;
        }
    }


    T &operator*() {
        return *ptr;
    }

    Iterator &operator--() {
        if ((ptr - 1) < ptr_start) {
            ptr = ptr_finish;
        } else {
            ptr--;
        }
        return *this;
    }

    Iterator operator-(difference_type rhs) {
        if (ptr - rhs < ptr_start) {
            int k = ptr - rhs - ptr_start;
            return Iterator(ptr_finish - k + 1, ptr_finish, ptr_start, flag, now_size, size_buffer);
        } else
            return Iterator(ptr - rhs, ptr_finish, ptr_start, flag, now_size, size_buffer);

    }

    Iterator operator+(difference_type rhs) {
        if (ptr + rhs > ptr_finish) {
            int k = ptr + rhs - ptr_finish;
            return Iterator(ptr_start + k - 1, ptr_finish, ptr_start, flag, now_size, size_buffer);
        } else
            return Iterator(ptr + rhs, ptr_finish, ptr_start, flag, now_size, size_buffer);

    }


    T &operator[](value_type value) {
        return ptr[value];
    }

    Iterator &operator+=(value_type value) {
        ptr = ptr + value;
        return *this;
    }

    Iterator &operator-=(value_type value) {
        ptr = ptr - value;
        return *this;

    }

    difference_type operator-(Iterator &rhs) {
        if ((ptr == rhs.ptr) && (now_size == size_buffer)) {
            return now_size;
        } else {
            if (ptr > rhs.ptr) {
                return ptr_finish - ptr + rhs.ptr - ptr_start + 1;
            } else {
                return ptr_finish - rhs.ptr + ptr - ptr_start + 1;
            }

        }
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
    T *ptr_arr_start;
    T *ptr_arr_finish;
    T *first_ptr;
    T *last_ptr;

public:

    CircularBuffer(int size = 0)
            : size_buffer(size) {
        circular_buffer = new T[size_buffer];
        ptr_arr_start = circular_buffer;
        ptr_arr_finish = circular_buffer + size_buffer - 1;
        first_ptr = circular_buffer + size_buffer - 1;
        last_ptr = circular_buffer;
    }

    ~CircularBuffer() {
        delete[]circular_buffer;
    }

    T first() {
        return *last_ptr;
    }

    T last() {
        return *first_ptr;
    }


    //fixed O(1)
    void addFirst(T value) {
        if (last_ptr == ptr_arr_start) {
            last_ptr = ptr_arr_finish;
        } else {
            last_ptr--;
        }
        *last_ptr = value;
        if (now_size < size_buffer) {
            now_size++;
        }


    }

    void delFirst() {
        if (last_ptr == ptr_arr_finish) {
            last_ptr = ptr_arr_start;
        } else {
            last_ptr++;
        }
        now_size--;

    }

    void addLast(T value) {
        if (first_ptr == ptr_arr_finish) {
            first_ptr = ptr_arr_start;
        } else {
            first_ptr++;
        }
        *first_ptr = value;
        if (now_size < size_buffer) {
            now_size++;
        }
    }

    void delLast() {
        if (first_ptr == ptr_arr_start) {
            first_ptr = ptr_arr_finish;
        } else {
            first_ptr--;
        }
        now_size--;
    }

    T &operator[](int x) const {
        if (x < 0 || x + 1 > now_size) {
            std::string str = "Out of range: now size - " + std::to_string(now_size);
            throw std::out_of_range(str);
        } else {
            int k = last_ptr + x - ptr_arr_finish;

            if (last_ptr + x > ptr_arr_finish) {
                return *(ptr_arr_start + k - 1);//last+x-size
            } else
                return *(last_ptr + x);

        }
    }

    T &operator[](int x) {
        if (x < 0 || x + 1 > now_size) {
            //fixed string into exception (size of buffer)
            std::string str = "Out of range: now size - " + std::to_string(now_size);
            throw std::out_of_range(str);
        } else {
            int k = last_ptr + x - ptr_arr_finish;

            if (last_ptr + x > ptr_arr_finish) {
                return *(ptr_arr_start + k - 1);
            } else
                return *(last_ptr + x);

        }
    }

    int flag = 0;
    int flag1 = 0;

    friend class Iterator<T>;

    Iterator<T> begin() const {
        return Iterator(last_ptr, ptr_arr_finish, ptr_arr_start, flag, now_size, size_buffer, flag1);
    }


    Iterator<T> end() const {
        return Iterator(last_ptr, ptr_arr_finish, ptr_arr_start, flag, now_size, size_buffer, flag1) + now_size;
    }


    void changeCapacity(int new_size) {
        now_size = std::min(now_size, new_size);
        T *buffer = new T[new_size];
        for (int i = 0; i < now_size; i++) {
            int k = last_ptr + i - ptr_arr_finish;
            if (last_ptr + i > ptr_arr_finish) {
                buffer[i] = *(ptr_arr_start + k - 1);
            } else
                buffer[i] = *(last_ptr + i);

        }
        //fixed memory
        size_buffer = new_size;
        delete[] circular_buffer;
        circular_buffer = buffer;
        ptr_arr_start = circular_buffer;
        ptr_arr_finish = circular_buffer + new_size - 1;
        first_ptr = circular_buffer + now_size - 1;
        last_ptr = circular_buffer;
    }


};


#endif //PROGA5LAB_CIRCULARBUFFER_HPP
