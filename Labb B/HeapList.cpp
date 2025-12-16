#ifndef HEAPLIST_HPP
#define HEAPLIST_HPP

#include "IndexedList.hpp"
#include <stdexcept>
#include <algorithm> // för std::swap

template <class T>
class HeapList {
private:
    IndexedList<T> list;

public:
    HeapList() = default;
    ~HeapList() = default;
    HeapList(const HeapList& other) = delete;
    HeapList& operator=(const HeapList& other) = delete;

    int size() const;
    bool isEmpty() const;
    void insert(const T& element);
    T extract();
    T peek() const;
};

template <class T>
int HeapList<T>::size() const {
    return list.size();
}

template <class T>
bool HeapList<T>::isEmpty() const {
    return list.isEmpty();
}

template <class T>
void HeapList<T>::insert(const T& element) {
    list.addAt(list.size(), element); // Lägg till sist
    int index = list.size() - 1;

    while (index > 0) {
        int parent = (index - 1) / 2;
        T childVal = list.getAt(index);
        T parentVal = list.getAt(parent);

        if (childVal > parentVal) {
            T temp = childVal;
            list.removeAt(index);
            list.addAt(index, parentVal);
            list.removeAt(parent);
            list.addAt(parent, temp);
            index = parent;
        }
        else {
            break;
        }
    }
}

template <class T>
T HeapList<T>::extract() {
    if (list.isEmpty())
        throw std::out_of_range("Heap is empty");

    T top = list.getAt(0);
    T last = list.removeLast();

    if (!list.isEmpty()) {
        list.removeAt(0);
        list.addAt(0, last);

        int index = 0;
        while (index * 2 + 1 < list.size()) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int largest = index;

            if (left < list.size() && list.getAt(left) > list.getAt(largest))
                largest = left;
            if (right < list.size() && list.getAt(right) > list.getAt(largest))
                largest = right;

            if (largest != index) {
                T indexVal = list.getAt(index);
                T largestVal = list.getAt(largest);

                if (index > largest) {
                    list.removeAt(index);
                    list.removeAt(largest);
                }
                else {
                    list.removeAt(largest);
                    list.removeAt(index);
                }

                list.addAt(index, largestVal);
                list.addAt(largest, indexVal);
                index = largest;
            }
            else {
                break;
            }
        }
    }

    return top;
}


template <class T>
T HeapList<T>::peek() const {
    if (list.isEmpty())
        throw std::out_of_range("Heap is empty");
    return list.getAt(0);
}

#endif
