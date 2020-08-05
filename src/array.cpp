#include "array.h"

template <class T, class Allocator>
void Array<T, Allocator>::resize(int newSize) {
    if (!newSize) {
        newSize = 1;
    }
    T* newArr = al.allocate(newSize);
    int minSize = ((aSize < newSize) ? aSize : newSize);
    for (int i = 0; i < minSize; i++) {
        newArr[i] = arr[i];
    }
    if (aCapacity > 0) {
        al.deallocate(arr, aCapacity);
    }
    arr = newArr;
    aCapacity = newSize;
}

template <class T, class Allocator>
Array<T, Allocator>::Array() {

}

template <class T, class Allocator>
Array<T, Allocator>::Array(int size) {
    if (!size) return;
    resize(size);
    aSize = size;
}

template <class T, class Allocator>
Array<T, Allocator>::Array(int size, T init) {
    if (!size) return;
    resize(size);
    aSize = size;
    for (int i = 0; i < size; i++) {
        arr[i] = init;
    }
}

template <class T, class Allocator>
Array<T, Allocator>::Array(Array&& obj) {
    aSize = obj.aSize;
    aCapacity = obj.aCapacity;
    arr = obj.arr;

    obj.aSize = 0;
    obj.aCapacity = 0;
    obj.arr = nullptr;
}

template <class T, class Allocator>
Array<T, Allocator>::Array(const Array& obj) {
    resize(obj.capacity());
    aSize = obj.size();

    for (int i = 0; i < obj.size(); i++) {
        arr[i] = obj[i];
    }
}

template <class T, class Allocator>
Array<T, Allocator>::~Array() {
     if (capacity() > 0) {
         al.deallocate(arr, capacity());
     }
}

template <class T, class Allocator>
int Array<T, Allocator>::size() const {
    return aSize;
}

template <class T, class Allocator>
int Array<T, Allocator>::capacity() const {
    return aCapacity;
}

template <class T, class Allocator>
bool Array<T, Allocator>::isEmpty() {
    return aSize == 0;
}

template <class T, class Allocator>
void Array<T, Allocator>::push(T item) {
    if (size() == capacity()) {
        resize(capacity() * 2);
    }
    arr[aSize++] = item;
}

template <class T, class Allocator>
void Array<T, Allocator>::insert(int index, T item) {
    if (size() == capacity()) {
        resize(capacity() * 2);
    }
    for (int i = size() - 1; i >= index; i--) {
        arr[i + 1] = arr[i];
    }
    arr[index] = item;
    aSize++;
}

template <class T, class Allocator>
void Array<T, Allocator>::unshift(T item) {
    insert(0, item);
}

template <class T, class Allocator>
T Array<T, Allocator>::pop() {
    T item = arr[--aSize];

    if (size() < capacity() / 4) {
        resize(capacity() / 2);
    }

    return item;
}

template <class T, class Allocator>
void Array<T, Allocator>::erase(int index) {
    for (int i = index; i < size() - 1; i++) {
        arr[i] = arr[i + 1];
    }
    aSize--;

    if (size() < capacity() / 4) {
        resize(capacity() / 2);
    }
}

template <class T, class Allocator>
void Array<T, Allocator>::remove(T item) {
    int removed = 0, p = 0;
    for (int i = 0; i < size(); i++) {
        if (arr[i] == item) {
            removed++;
        } else {
            arr[p++] = arr[i];
        }
    }
    aSize -= removed;

    if (size() < capacity() / 4) {
        resize(capacity() / 2);
    }
}

template <class T, class Allocator>
void Array<T, Allocator>::clear() {
    if (capacity() > 0) {
        al.deallocate(arr, capacity());
    }
    aSize = 0;
    aCapacity = 0;
}

template <class T, class Allocator>
typename Array<T, Allocator>::iterator Array<T, Allocator>::find(T item) {
    for (int i = 0; i < size(); i++) {
        if (arr[i] == item) {
            return iterator(arr + i);
        }
    }
    return end();
}

template <class T, class Allocator>
T& Array<T, Allocator>::operator[] (int index) {
    // TODO: How should the out of bounds error be handled?
    return arr[index];
}

template <class T, class Allocator>
const T& Array<T, Allocator>::operator[] (int index) const {
    return arr[index];
}

template <class T, class Allocator>
Array<T, Allocator>& Array<T, Allocator>::operator= (const Array& obj) {
    if (this == &obj) {
        return *this;
    }
    resize(obj.capacity());
    aSize = obj.size();

    for (int i = 0; i < obj.size(); i++) {
        arr[i] = obj[i];
    }

    return *this;
}

template <class T, class Allocator>
Array<T, Allocator>& Array<T, Allocator>::operator=(Array&& obj) {
    aSize = obj.aSize;
    aCapacity = obj.aCapacity;
    arr = obj.arr;

    obj.aSize = 0;
    obj.aCapacity = 0;
    obj.arr = nullptr;

    return *this;
}