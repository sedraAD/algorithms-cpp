#ifndef STACKARRAY_H
#define STACKARRAY_H
#include <stdexcept>

template <typename T>
class StackArray
{
private:
	T* elements;
	int capacity;
	int topIndex;

	void resize();

public:
	StackArray(int initialCapacity = 10);
	virtual ~StackArray();
	StackArray(const StackArray& other) = delete;
	StackArray& operator=(const StackArray& other) = delete;
	void push(const T& element);
	T pop();
	const T& peek() const;
	bool isEmpty()const;
	int size() const;
};

template<typename T>
inline StackArray<T>::StackArray(int initialCapacity)
	: capacity(initialCapacity), topIndex(0)
{
	elements = new T[capacity];
}

template<typename T>
inline StackArray<T>::~StackArray()
{
	delete[] elements;
}


template<typename T>
inline void StackArray<T>::resize()
{
	capacity *= 2;
	T* newElements = new T[capacity];

	for (int i = 0; i < topIndex; ++i) {
		newElements[i] = elements[i];
	}

	delete[] elements;
	elements = newElements;

}

template<typename T>
inline void StackArray<T>::push(const T& element)
{
	if (topIndex == capacity) {
		resize();
	}
	elements[topIndex++] = element;
}

template<typename T>
inline T StackArray<T>::pop()
{
	if (isEmpty()) {
		throw std::runtime_error("Stack is empty");
	}
	return elements[--topIndex];
}

template<typename T>
inline const T& StackArray<T>::peek() const
{
	if (isEmpty()) {
		throw std::runtime_error("Stack is empty");

	}
	return elements[topIndex - 1];
}

template<typename T>
inline bool StackArray<T>::isEmpty()const
{
	return topIndex == 0;
}

template<typename T>
inline int StackArray<T>::size()const
{
	return topIndex;
}

#endif
