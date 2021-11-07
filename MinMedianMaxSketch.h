#ifdef MINMEDIANMAXSKETCH_H
#define MINMEDIANMAXSKETCH_H

template <class T>
class minMedianMax
{
private:
    int minSize;
    int maxSize;
    T min;
    T max;
    std::vector<T> min_heap;
    std::vector<T> max_heap;

public:
    minMedianMax(T max[], T min[]);
    void insert(T el);
    void remove(T el);
    T get_median();
    T get_minimum();
    T get_maximum();
    int get_size();
    bool search(T el);
    bool compare(T a, T b);
};

#endif