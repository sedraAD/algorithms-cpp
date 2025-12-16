#ifndef A1_HPP
#define A1_HPP
#include <algorithm>	// Included for use of std::swap()

template <class T>
int LinearSearch(T elements[], int nrOfElements, T element)
{
    for (int i = 0; i < nrOfElements; i++)
    {
        if (elements[i] == element)
        {
            return i;
        }
    }
    return -1;
}

template <class T>
void Selectionsort(T elements[], int nrOfElements)
{
    for (int i = 0; i < nrOfElements - 1; i++)
    {
        int minimumIndex = i;
        for (int j = i + 1; j < nrOfElements; j++)
        {
            if (elements[j] < elements[minimumIndex])
            {
                minimumIndex = j;
            }
        }
        std::swap(elements[i], elements[minimumIndex]);
    }
}

template <class T>
void Insertionsort(T elements[], int nrOfElements)
{
    for (int i = 1; i < nrOfElements; i++)
    {
        T key = elements[i];
        int j = i - 1;
        while (j >= 0 && elements[j] > key)
        {
            elements[j + 1] = elements[j];
            j--;
        }
        elements[j + 1] = key;
    }
}

template <class T>
int BinarySearch(T elements[], int nrOfElements, T element)
{
    int low = 0;
    int high = nrOfElements - 1;
    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (element == elements[mid])
        {
            return mid;
        }
        else if (element < elements[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

template <class T>
int LinearSearchRecursive(T elements[], int nrOfElements, T element)
{
    if (nrOfElements <= 0)
        return -1;
    if (elements[0] == element)
        return 0;
    int result = LinearSearchRecursive(elements + 1, nrOfElements - 1, element);
    if (result == -1)
        return -1;
    else
        return result + 1;
}

template <class T>
int BinarySearchRecursive(T elements[], int nrOfElements, T element)
{
    int low = 0;
    int high = nrOfElements - 1;
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (elements[mid] == element)
        return mid;
    else if (elements[mid] > element)
        return BinarySearchRecursive(elements, mid, element);
    else {
        int result = BinarySearchRecursive(elements + mid + 1, nrOfElements - mid - 1, element);
        if (result == -1)
            return -1;
        else
            return result + mid + 1;
    }
}


template <class T>
void Merge(T* elements, T* left, T* right, int nrOfElements, int leftNrOfElements, int rightNrOfElements)
{
    int i = 0, j = 0, k = 0;

    while (j < leftNrOfElements and k < rightNrOfElements)
    {
        if (left[j] <= right[k])
        {
            elements[i] = left[j];
            ++j;
        }
        else
        {
            elements[i] = right[k];
            ++k;
        }
        ++i;
    }

    while (j < leftNrOfElements)
    {
        elements[i] = left[j];
        ++i;
        ++j;
    }
    while (k < rightNrOfElements)
    {
        elements[i] = right[k];
        ++i;
        ++k;
    }
}

template <class T>
void Mergesort(T elements[], int nrOfElements)
{
    if (nrOfElements > 1)
    {
        int leftNrOfElements = nrOfElements / 2;
        int rightNrOfElements = nrOfElements - leftNrOfElements;
        T* left = new T[leftNrOfElements];
        T* right = new T[rightNrOfElements];

        for (int i = 0; i < leftNrOfElements; i++)
            left[i] = elements[i];
        for (int i = 0; i < rightNrOfElements; i++)
            right[i] = elements[i + leftNrOfElements];

        Mergesort(left, leftNrOfElements);
        Mergesort(right, rightNrOfElements);
        Merge(elements, left, right, nrOfElements, leftNrOfElements, rightNrOfElements);
    }
}

template <class T>
void MergeBook(T elements[], int start, int mid, int end)
{
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    T* left = new T[leftSize];
    T* right = new T[rightSize];

    for (int i = 0; i < leftSize; i++) {
        left[i] = elements[start + i];
    }
    for (int i = 0; i < rightSize; i++) {
        right[i] = elements[mid + 1 + i];
    }

    int i = 0, j = 0, k = start;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            elements[k++] = left[i++];
        }
        else {
            elements[k++] = right[j++];
        }
    }
    while (i < leftSize) {
        elements[k++] = left[i++];
    }
    while (j < rightSize) {
        elements[k++] = right[j++];
    }

    delete[] left;
    delete[] right;
}

template <class T>
void MergesortBook(T elements[], int nrOfElements)
{
    if (nrOfElements < 2)
        return;

    int start = 0;
    int end = nrOfElements - 1;

    if (start < end) {
        int mid = (start + end) / 2;

        MergesortBook(elements, mid + 1);
        MergesortBook(elements + mid + 1, nrOfElements - mid - 1);

        MergeBook(elements, start, mid, end);
    }
}

template <class T>
int PartitionLomuto(T elements[], int start, int end)
{
    int pivot = elements[end];
    int i = start;

    for (int j = start; j <= end - 1; j++)
    {
        if (elements[j] < pivot)
        {
            std::swap(elements[i], elements[j]);
            i++;
        }
    }

    std::swap(elements[i], elements[end]);
    return i;
}


template <class T>
void QuicksortLomutoRecursive(T elements[], int start, int end)
{
    if (start < end)
    {
        int pivot = PartitionLomuto(elements, start, end);
        QuicksortLomutoRecursive(elements, start, pivot - 1);
        QuicksortLomutoRecursive(elements, pivot + 1, end);
    }
}

template <class T>
void QuicksortLomuto(T elements[], int nrOfElements)
{
    QuicksortLomutoRecursive(elements, 0, nrOfElements - 1);
}

template <class T>
void QuicksortHoare(T elements[], int nrOfElements)
{
    if (nrOfElements < 2) return;

    T pivot = elements[0];
    int i = -1, j = nrOfElements;

    do {
        while (elements[++i] < pivot);
        while (elements[--j] > pivot);
        if (i < j) std::swap(elements[i], elements[j]);
    } while (i < j);

    QuicksortHoare(elements, j + 1);
    QuicksortHoare(elements + j + 1, nrOfElements - j - 1);
}

template <class T>
int MedianOfThree(T elements[], int start, int end)
{
    int mid = (start + end) / 2;
    if ((elements[start] <= elements[mid] && elements[mid] <= elements[end]) || (elements[start] >= elements[mid] and elements[mid] >= elements[end]))
        return mid;
    if ((elements[mid] <= elements[start] && elements[start] <= elements[end]) || (elements[mid] >= elements[start] and elements[start] >= elements[end]))
        return start;
    return end;
}

template <class T>
void heapify(T arr[], int heapSize, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < heapSize && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, heapSize, largest);
    }
}

template <class T>
void Heapsort(T arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }

    for (int end = n - 1; end > 0; --end) {
        std::swap(arr[0], arr[end]);
        heapify(arr, end, 0);
    }
}


#endif
