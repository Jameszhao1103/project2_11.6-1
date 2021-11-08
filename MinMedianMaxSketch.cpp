#include "MinMedianMaxSketch.h"

#include <iostream>
#include <vector>
#include <cmath>

template <class T>
bool minComparer(T a, T b)
{
    return a < b;
}

template <class T>
bool maxComparer(T a, T b)
{
    return a > b;
}

template <class T>
minMedianMax<T>::minMedianMax(int inMinSize, int inMaxSize, std::vector<T> min, std::vector<T> max)
{
    for (int i = 0; i < inMinSize; i++)
    {
        minMedianMax<T>::insert(true, min[i]);
    }
    for (int j = 0; j < inMaxSize; j++)
    {
        minMedianMax<T>::insert(false, max[j]);
    }
    std::cout << "min_size" << minSize << std::endl;
    std::cout << "max_size" << maxSize << std::endl;
}

template <class T>
void minMedianMax<T>::ShiftDown(bool (*func)(T a, T b), int index, std::vector<T> heap)
{
    int length = heap.size();
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left >= length)
        return;

    int rootIndex = index;

    if (func(heap[left], heap[index]))
    {
        rootIndex = left;
    }

    if ((right < length) && (func(heap[right], heap[rootIndex])))
    {
        rootIndex = right;
    }

    if (rootIndex != index)
    {
        int temp = heap[index];
        heap[index] = heap[rootIndex];
        heap[rootIndex] = temp;
        ShiftDown(func, rootIndex, heap);
    }
}

template <class T>
void minMedianMax<T>::ShiftUp(bool (*func)(T a, T b), int index, std::vector<T> heap)
{
    if (index == 0)
        return;

    int parent = (index - 1) / 2;

    if (func(heap[index], heap[parent]))
    {
        int temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        ShiftUp(func, parent, heap);
    }
}

template <class T>
void minMedianMax<T>::insert(bool isMin, T el)
{
    bool (*func)(T, T);
    if (isMin)
    {
        minSize++;
        min_heap.resize(minSize);
        min_heap[minSize] = el;
        func = &minComparer;
        ShiftUp(func, minSize, min_heap);
    }
    else
    {
        maxSize++;
        max_heap.resize(maxSize);
        max_heap[maxSize] = el;
        func = &maxComparer;
        ShiftUp(func, maxSize, max_heap);
    }
    rebalance();
}

template <class T>
void minMedianMax<T>::remove(T el)
{
    if (el >= min)
    {
        for (int i = 0; i < min_heap.size(); i++)
        {
            if (min_heap[i] == el)
            {
                min_heap[i] = min_heap[minSize - 1];
                minSize--;
                min_heap.resize(minSize);
                heapify(true, minSize);
            }
        }
    }
    else if (el <= max)
    {
        for (int i = 0; i < max_heap.size(); i++)
        {
            if (max_heap[i] == el)
            {
                max_heap[i] = max_heap[maxSize - 1];
                maxSize--;
                max_heap.resize(maxSize);
                heapify(false, maxSize);
            }
        }
    }
    rebalance();
}

template <class T>
void minMedianMax<T>::heapify(bool isMin, int size)
{
    bool (*func)(T, T);
    if (isMin)
    {
        func = &minComparer;
        for (int i = size; i > 0; --i)
        {
            ShiftDown(func, i, min_heap);
        }
    }
    else
    {
        func = &maxComparer;
        for (int i = size; i > 0; --i)
        {
            ShiftDown(func, i, max_heap);
        }
    }
}

template <class T>
T minMedianMax<T>::get_median()
{
    if (minSize > maxSize)
        return min;
    else
        return max;
}

template <class T>
T minMedianMax<T>::get_minimum()
{
    return min;
}

template <class T>
T minMedianMax<T>::get_maximum()
{
    return max;
}

template <class T>
int minMedianMax<T>::get_size()
{
    return minSize + maxSize;
}

template <class T>
bool minMedianMax<T>::search(T el)
{
    for (int i = 0; i < min_heap.size(); i++)
    {
        if (min_heap[i] == el)
            return true;
    }
    for (int i = 0; i < max_heap.size(); i++)
    {
        if (max_heap[i] == el)
            return true;
    }
    return false;
}

template <class T>
void minMedianMax<T>::rebalance()
{
    min = min_heap[0];
    max = max_heap[0];
    if (maxSize - minSize > 1)
    {
        T temp = max_heap[0];
        remove(max_heap[0]);
        insert(true, temp);
    }
    else if (minSize - maxSize > 1)
    {
        T temp = min_heap[0];
        remove(min_heap[0]);
        insert(false, temp);
    }
    return;
}
