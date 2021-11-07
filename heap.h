#ifdef HEAP_H
#define HEAP_H

template <class T>
class heap
{
private:
    bool isMin;
    int size;
    std::vector<T> MinMaxHeap;

public:
    heap(bool isMin);
    void insert(T el);
    void remove(T el);
    T get_root();
    T extract_root();
    T get_min();
    T get_max();
    int get_size();
    bool search(T input);
    bool compare(T a, T b);
};

#endif