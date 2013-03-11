#ifndef QUICKUNION_H
#define QUICKUNION_H

#include <vector>

template<class T>
class QuickUnion
{
public:
    explicit QuickUnion(int _size);
    void join(T a, T b);
    T root(T s);
    void print();
private:
    std::vector<T> parent;
    T size;
};

#endif // QUICKUNION_H
