#ifndef MINMEDIANMAXSKETCH_H
#define MINMEDIANMAXSKETCH_H

#include <vector>

template <class T>
class minMedianMax
{
private:
    int minSize = 0;
    int maxSize = 0;
    T min;
    T max;
    std::vector<T> min_heap;
    std::vector<T> max_heap;

public:
    minMedianMax(int inMinSize, int inMaxSize, std::vector<T> min, std::vector<T> max);
    void insert(bool isMin, T el, bool isNewElement);
    void ShiftDown(bool (*func)(T a, T b), int index, std::vector<T> heap);
    void ShiftUp(bool (*func)(T a, T b), int index, std::vector<T> heap);
    void remove(T el);
    void heapify(bool isMin, int size);
    T get_median();
    T get_minimum();
    T get_maximum();
    int get_size();
    bool search(T el);
    void rebalance(bool isMin, bool inConstructor);
};

#endif
