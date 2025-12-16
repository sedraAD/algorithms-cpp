#ifndef HEAP_HPP
#define HEAP_HPP

#include <stdexcept>
#include <algorithm> // för std::swap

template <class T>
class Heap {
private:
    int capacity;
    int nrOfElements;
    T* elements;w

    void expand();

public:
    Heap(int initialCapacity = 10);
    ~Heap();
    Heap(const Heap& other) = delete;
    Heap& operator=(const Heap& other) = delete;

    int size() const;
    bool isEmpty() const;
    void insert(const T& element);
    T extract();
    T peek() const;
};

template <class T>
Heap<T>::Heap(int initialCapacity)
    : capacity(initialCapacity), nrOfElements(0), elements(new T[initialCapacity]) {}

template <class T>
Heap<T>::~Heap() {
    delete[] elements;
}

template <class T>
void Heap<T>::expand() {
    this->capacity *= 2;
    T* newArr = new T[capacity];
    for (int i = 0; i < nrOfElements; i++)
        newArr[i] = elements[i];
    delete[] elements;
    elements = newArr;
}

template <class T>
int Heap<T>::size() const {
    return nrOfElements;
}

template <class T>
bool Heap<T>::isEmpty() const {
    return nrOfElements == 0;
}

template <class T>
void Heap<T>::insert(const T& element) {
    if (nrOfElements >= capacity)
        expand();

    int index = nrOfElements;
    elements[nrOfElements++] = element;

    while (index > 0) {
        int parent = (index - 1) / 2;
        if (elements[index] > elements[parent]) {
            std::swap(elements[index], elements[parent]);
            index = parent;
        }
        else {
            break;
        }
    }
}

template <class T>
T Heap<T>::extract() {
    if (isEmpty())
        throw std::out_of_range("Heap is empty");

    T top = elements[0];
    elements[0] = elements[--nrOfElements];

    int index = 0;
    while (index * 2 + 1 < nrOfElements) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < nrOfElements && elements[left] > elements[largest])
            largest = left;
        if (right < nrOfElements && elements[right] > elements[largest])
            largest = right;

        if (largest != index) {
            std::swap(elements[index], elements[largest]);
            index = largest;
        }
        else {
            break;
        }
    }

    return top;
}

template <class T>
T Heap<T>::peek() const {
    if (isEmpty())
        throw std::out_of_range("Heap is empty");
    return elements[0];
}

#endif
