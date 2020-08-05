#ifndef CPP_DATA_STRUCTURES_ARRAY_H
#define CPP_DATA_STRUCTURES_ARRAY_H

#include <memory>

template <class T, class Allocator = std::allocator<T> >
class Array {
public:
    class iterator {
    public:
        iterator(T * ptr): ptr(ptr){}
        iterator operator++() { ++ptr; return *this; }
        bool operator!=(const iterator & other) const { return ptr != other.ptr; }
        bool operator==(const iterator & other) const { return ptr == other.ptr; }
        const T& operator*() const { return *ptr; }
    private:
        T* ptr;
    };
private:
    T* arr;
    Allocator al;
    int aSize = 0, aCapacity = 0;
    void resize(int);
public:
    Array();
    Array(int);
    Array(int, T);
    Array(const Array&);
    Array(Array&&);
    ~Array();

    iterator begin() const { return iterator(arr); }
    iterator end() const { return iterator(arr + aSize); }

    int size() const;
    int capacity() const;
    bool isEmpty();
    void push(T);
    void insert(int, T);
    void unshift(T);
    T pop();
    void erase(int);
    void remove(T);
    iterator find(T);
    void clear();

    T& operator[] (int);
    const T& operator[] (int) const;
    Array& operator=(const Array&);
    Array& operator=(Array&&);
};

#endif //CPP_DATA_STRUCTURES_ARRAY_H
