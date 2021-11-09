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
minMedianMax<T>::minMedianMax(int inMinSize, int inMaxSize, std::vector<T> inMin, std::vector<T> inMax)
{
    min_heap.resize(inMinSize);
    max_heap.resize(inMaxSize);
    min = inMax[0];
    max = inMin[inMinSize - 1];
    for (int i = 0; i < inMinSize; i++)
    {
        // std::cout << min[i] << std::endl;
        minMedianMax<T>::insert(true, inMin[i], true);
    }
    for (int j = 0; j < inMaxSize; j++)
    {
        minMedianMax<T>::insert(false, inMax[j], true);
    }
    min = min_heap[0];
    max = max_heap[0];
}

template <class T>
void minMedianMax<T>::ShiftDown(bool (*func)(T a, T b), int index, std::vector<T> &heap)
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
void minMedianMax<T>::ShiftUp(bool (*func)(T a, T b), int index, std::vector<T> &heap)
{
    if (index == 0)
        return;

    int parent = (index - 1) / 2;

    if (func(heap[index], heap[parent]))
    {
        T temp = heap[parent];
        heap[parent] = heap[index];
        heap[index] = temp;
        ShiftUp(func, parent, heap);
    }
}

template <class T>
void minMedianMax<T>::insert(bool isMin, T el, bool inConstructor)
{

    if (isMin)
    {
        minSize++;
        if (!inConstructor)
        {
            min_heap.resize(minSize);
        }
        min_heap[minSize - 1] = el;
        bool (*func)(T, T) = minComparer;
        ShiftUp(func, minSize - 1, min_heap);
        rebalance(isMin, inConstructor);
    }
    else
    {
        maxSize++;
        if (!inConstructor)
        {
            max_heap.resize(maxSize);
        }
        max_heap[maxSize - 1] = el;
        bool (*func)(T, T) = maxComparer;
        ShiftUp(func, maxSize - 1, max_heap);
        rebalance(isMin, inConstructor);
    }
}
template <class T>
T minMedianMax<T>::getMaxheap(int i)
{
    return max_heap[i];
}

template <class T>
T minMedianMax<T>::getMinheap(int i)
{
    return min_heap[i];
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
                rebalance(true, false);
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
                rebalance(false, false);
            }
        }
    }
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
    {
        return min_heap[0];
    }
    else
    {
        return max_heap[0];
    }
}

template <class T>
T minMedianMax<T>::get_minimum()
{
    int minimum = 9999;
    for (int i = 0; i < maxSize; i++)
    {
        if (max_heap[i] < minimum)
        {
            minimum = max_heap[i];
        }
    }

    return minimum;
}

template <class T>
T minMedianMax<T>::get_maximum()
{
    int maximum = -9999;
    for (int i = 0; i < maxSize; i++)
    {
        if (min_heap[i] > maximum)
        {
            maximum = min_heap[i];
        }
    }

    return maximum;
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
void minMedianMax<T>::rebalance(bool isMin, bool inConstructor)
{
    //Three special situation
    if (inConstructor)
        return;
    if (isMin && minSize == 1)
        return;
    if (!isMin && maxSize == 1)
        return;
    if (minSize == maxSize)
        return;

    min = min_heap[0];
    //std::cout << "hi" << min << std::endl;
    max = max_heap[0];
    //std::cout << "hi" << max << std::endl;

    if (maxSize - minSize > 1)
    {

        T temp = max_heap[0];

        remove(max_heap[0]);
        insert(true, temp, false);
    }
    else if (minSize - maxSize > 1)
    {
        T temp = min_heap[0];
        remove(min_heap[0]);
        insert(false, temp, false);
    }
    return;
}
