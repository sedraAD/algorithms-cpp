#ifndef ORDEREDLIST_HPP
#define ORDEREDLIST_HPP

#include <stdexcept>

template <class T>
class OrderedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    int num_elements;

public:
    OrderedList();
    ~OrderedList();
    OrderedList(const OrderedList& other) = delete;
    OrderedList& operator=(const OrderedList& other) = delete;

    int size() const;
    bool isEmpty() const;
    void add(const T& element);
    T remove(const T& element);
    T removeAt(int index);
    T removeFirst();
    T removeLast();
    T get(const T& element) const;
    T first() const;
    T last() const;
};

template <class T>
OrderedList<T>::OrderedList()
    : front(nullptr), num_elements(0) {}

template <class T>
OrderedList<T>::~OrderedList() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
}

template <class T>
int OrderedList<T>::size() const {
    return num_elements;
}

template <class T>
bool OrderedList<T>::isEmpty() const {
    return num_elements == 0;
}

template <class T>
void OrderedList<T>::add(const T& element) {
    Node* newNode = new Node(element);

    if (front == nullptr || element < front->data) {
        newNode->next = front;
        front = newNode;
    }
    else {
        Node* current = front;
        while (current->next != nullptr && current->next->data < element)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    num_elements++;
}

template <class T>
T OrderedList<T>::remove(const T& element) {
    // Removes and returns specific element from the OrderedList
    if (isEmpty()) throw std::runtime_error("List is empty");

    if (front->data == element) {
        return removeFirst();
    }

    Node* current = front;
    while (current->next != nullptr && current->next->data != element) {
        current = current->next;
    }

    if (current->next == nullptr) throw std::runtime_error("Element not found");

    Node* temp = current->next;
    T data = temp->data;
    current->next = temp->next;
    delete temp;
    --num_elements;
    return data;
}

template <class T>
T OrderedList<T>::removeAt(int index) {
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
T OrderedList<T>::removeFirst() {
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
T OrderedList<T>::removeLast() {
    if (isEmpty())
        throw std::out_of_range("List is empty");

    return removeAt(num_elements - 1);
}

template <class T>
T OrderedList<T>::get(const T& element) const {
    Node* current = front;
    while (current != nullptr) {
        if (current->data == element)
            return current->data;
        current = current->next;
    }

    throw std::runtime_error("Element not found");
}

template <class T>
T OrderedList<T>::first() const {
    if (isEmpty())
        throw std::out_of_range("List is empty");
    return front->data;
}

template <class T>
T OrderedList<T>::last() const {
    if (isEmpty())
        throw std::out_of_range("List is empty");

    Node* current = front;
    while (current->next != nullptr)
        current = current->next;

    return current->data;
}

#endif