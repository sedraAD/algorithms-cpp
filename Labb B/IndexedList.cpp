#ifndef INDEXEDLIST_HPP
#define INDEXEDLIST_HPP

#include <stdexcept>

template <class T>
class IndexedList {
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(T data = T()) : data(data), next(nullptr) {}
    };
    Node* front;
    int num_elements;

public:
    IndexedList();
    ~IndexedList();
    IndexedList(const IndexedList& other) = delete;
    IndexedList& operator=(const IndexedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    T getAt(int index) const;
    T get(T element) const;
    void addAt(int index, const T& element);
    T removeFirst();
    T removeAt(int index);
    T removeLast();
    T first() const;
    T last() const;
};

template<class T>
IndexedList<T>::IndexedList() {
    front = nullptr;
    num_elements = 0;
}

template <class T>
IndexedList<T>::~IndexedList() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

template <class T>
int IndexedList<T>::size() const {
    return num_elements;
}

template <class T>
bool IndexedList<T>::isEmpty() const {
    return num_elements == 0;
}

template <class T>
T IndexedList<T>::getAt(int index) const {
    if (index < 0 || index >= num_elements)
        throw std::out_of_range("Index out of range");

    Node* current = front;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current->data;
}
 
template <class T>
T IndexedList<T>::get(T element) const {
    Node* current = front;
    while (current != nullptr) {
        if (current->data == element)
            return current->data;
        current = current->next;
    }
    throw std::runtime_error("Element not found");
}

template <class T>
void IndexedList<T>::addAt(int index, const T& element) {
    if (index < 0 || index > num_elements)
        throw std::out_of_range("Index out of range");

    Node* newNode = new Node(element);

    if (index == 0) {
        newNode->next = front;
        front = newNode;
    }
    else {
        Node* current = front;
        for (int i = 0; i < index - 1; i++)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    num_elements++;
}

template <class T>
T IndexedList<T>::removeFirst() {
    if (isEmpty())
        throw std::out_of_range("List is empty");

    Node* temp = front;
    T value = temp->data;
    front = front->next;
    delete temp;
    num_elements--;
    return value;
}

template <class T>
T IndexedList<T>::removeAt(int index) {
    if (index < 0 || index >= num_elements)
        throw std::out_of_range("Index out of range");

    if (index == 0)
        return removeFirst();

    Node* current = front;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    Node* toDelete = current->next;
    T value = toDelete->data;
    current->next = toDelete->next;
    delete toDelete;
    num_elements--;
    return value;
}

template <class T>
T IndexedList<T>::removeLast() {
    if (isEmpty())
        throw std::out_of_range("List is empty");

    return removeAt(num_elements - 1);
}

template <class T>
T IndexedList<T>::first() const {
    if (isEmpty())
        throw std::out_of_range("List is empty");
    return front->data;
}

template <class T>
T IndexedList<T>::last() const {
    if (isEmpty())
        throw std::out_of_range("List is empty");

    Node* current = front;
    while (current->next != nullptr)
        current = current->next;
    return current->data;
}

#endif

