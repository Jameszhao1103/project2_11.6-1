#include "MinMedianMaxSketch.h"

#include <iostream>
#include <cmath>

using namespace std;

template <class T>
minMedianMax<T>::minMedianMax(int inMinSize, int inMaxSize, T min[], T max[])
{
    for (int i = 0; i < minSize; i++)
    {
        insert(true, min[i]);
    }
    for (int j = 0; j < maxSize; j++)
    {
        insert(false, max[j]);
    }
}

template <class T>
void minMedianMax<T>::BubbleDown(bool (*func)(T a, T b), int index, vector<T> heap)
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
void minMedianMax<T>::BubbleUp(bool (*func)(T a, T b), int index, vector<T> heap)
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
    bool (*func)(T, T);
    if (isMin)
    {
        minSize++;
        min_heap.resize(minSize);
        func = &minComparer;
        min_heap[minSize] = el;
        BubbleUp(func, minSize, min_heap);
    }
    else
    {
        maxSize++;
        max_heap.resize(maxSize);
        func = &maxComparer;
        max_heap[maxSize] = el;
        BubbleUp(func, maxSize, max_heap);
    }
}

template <class T>
void minMedianMax<T>::remove(T el)
{
}

template <class T>
void minMedianMax<T>::heapify(bool isMin, int size)
{
    if (isMin)
    {
        for (int i = size; i > 0; --i)
        {
            BubbleDown(i);
        }
    }
    else
    {
        for (int i = size; i > 0; --i)
        {
            BubbleDown(i);
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
}

template <class T>
bool minMedianMax<T>::isBalanced()
{
    return abs(minSize - maxSize) <= 1;
}