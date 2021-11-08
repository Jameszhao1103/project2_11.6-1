#include "MinMedianMaxSketch.h"

#include <iostream>
#include <vector>
#include <cmath>

// using namespace std;

template <class T>
minMedianMax<T>::minMedianMax(int inMinSize, int inMaxSize, std::vector<T> min, std::vector<T> max)
{
    for (int i = 0; i < minSize; i++)
    {
        minMedianMax<T>::insert(true, min.at(i));
    }
    for (int j = 0; j < maxSize; j++)
    {
        minMedianMax<T>::insert(false, max.at(j));
    }
}

template <class T>
void minMedianMax<T>::BubbleDown(bool (*func)(T a, T b), int index, std::vector<T> heap)
{
    int length = heap.size();
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;

    if (leftChildIndex >= length)
        return;

    int rootIndex = index;

    if (func(heap[leftChildIndex], heap[index]))
    {
        rootIndex = leftChildIndex;
    }

    if ((rightChildIndex < length) && (func(heap[rightChildIndex], heap[rootIndex])))
    {
        rootIndex = rightChildIndex;
    }

    if (rootIndex != index)
    {
        int temp = heap[index];
        heap[index] = heap[rootIndex];
        heap[rootIndex] = temp;
        BubbleDown(func, rootIndex, heap);
    }
}

template <class T>
void minMedianMax<T>::BubbleUp(bool (*func)(T a, T b), int index, std::vector<T> heap)
{
    if (index == 0)
        return;

    int parentIndex = (index - 1) / 2;

    if (func(heap[index], heap[parentIndex]))
    {
        int temp = heap[parentIndex];
        heap[parentIndex] = heap[index];
        heap[index] = temp;
        BubbleUp(func, parentIndex, heap);
    }
}

template <class T>
void minMedianMax<T>::insert(bool isMin, T el)
{
    bool (minMedianMax<T>::*func)(T, T);
    if (isMin)
    {
        minSize++;
        min_heap.resize(minSize);
        min_heap[minSize] = el;
        func = &minMedianMax<T>::minComparer;
        BubbleUp(func, minSize, min_heap);
    }
    else
    {
        maxSize++;
        max_heap.resize(maxSize);
        max_heap[maxSize] = el;
        func = &minMedianMax<T>::maxComparer;
        BubbleUp(func, maxSize, max_heap);
    }
}

template <class T>
void minMedianMax<T>::remove(T el)
{
    for (int i = 0; i < min_heap.size(); i++)
    {
        if (min_heap[i] == el)
        {
            min_heap[i] = min_heap[minSize - 1];
            minSize--;
            min_heap.resize(minSize);
            heapify(true, minSize);
            if (maxSize - minSize > 1)
            {
                T temp = max_heap[0];
                remove(max_heap[0]);
                insert(true, temp);
            }
            return;
        }
    }
    for (int i = 0; i < max_heap.size(); i++)
    {
        if (max_heap[i] == el)
        {
            max_heap[i] = max_heap[maxSize - 1];
            maxSize--;
            max_heap.resize(maxSize);
            heapify(false, maxSize);
            if (minSize - maxSize > 1)
            {
                T temp = min_heap[0];
                remove(min_heap[0]);
                insert(false, temp);
            }
            return;
        }
    }
}

template <class T>
void minMedianMax<T>::heapify(bool isMin, int size)
{
    bool (minMedianMax<T>::*func)(T, T);
    if (isMin)
    {
        func = &minMedianMax<T>::minComparer;
        for (int i = size; i > 0; --i)
        {
            BubbleDown(func, i, min_heap);
        }
    }
    else
    {
        func = &minMedianMax<T>::maxComparer;
        for (int i = size; i > 0; --i)
        {
            BubbleDown(func, i, max_heap);
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
