#ifndef PRIORITYQUEUEHEAP_HPP
#define PRIORITYQUEUEHEAP_HPP

#include "Heap.hpp"
#include <stdexcept>

template <typename T>
class PriorityQueueHeap {
private:
    Heap<T> heap;

public:
    PriorityQueueHeap();
    ~PriorityQueueHeap() = default;
    PriorityQueueHeap(const PriorityQueueHeap& other) = delete;
    PriorityQueueHeap& operator =(const PriorityQueueHeap& other) = delete;

    int size() const;
    void enqueue(const T& element);
    T dequeue();
    T peek() const;
    bool isEmpty() const;
};

template <class T>
PriorityQueueHeap<T>::PriorityQueueHeap()
{

}

template <class T>
int PriorityQueueHeap<T>::size() const {
    // Returns size of PQ
    return heap.size();
}

template <class T>
void PriorityQueueHeap<T>::enqueue(const T& element) {
    // Add to PQ
    heap.insert(element);
}

template <class T>
T PriorityQueueHeap<T>::dequeue() {
    // Remove and return next element from PQ
    return heap.extract();
}

template <class T>
T PriorityQueueHeap<T>::peek() const {
    // Returns next element from PQ
    return heap.peek();
}

template <class T>
bool PriorityQueueHeap<T>::isEmpty() const {
    // Returns if empty or not
    return heap.isEmpty();
}

#endif
