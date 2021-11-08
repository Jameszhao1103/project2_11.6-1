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
    void insert(bool isMin, T el);
    void BubbleDown(bool (*func)(T a, T b), int index, std::vector<T> heap);
    void BubbleUp(bool (*func)(T a, T b), int index, std::vector<T> heap);
    void remove(T el);
    void heapify(bool isMin, int size);
    T get_median();
    T get_minimum();
    T get_maximum();
    int get_size();
    bool search(T el);
    bool minComparer(T a, T b);
    bool maxComparer(T a, T b);
};

#endif
