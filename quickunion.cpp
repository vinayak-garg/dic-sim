#include "quickunion.h"

#include <iostream>

template<class T>
QuickUnion<T>::QuickUnion(int _size) : parent(_size), size(_size)
{
    for (int i = 0; i < size; i++)
        parent[i] = i;
}

template<class T>
void QuickUnion<T>::join(T a, T b)
{
    T rootA = root(a);
    T rootB = root(b);
    parent[rootB] = rootA;
}

template<class T>
T QuickUnion<T>::root(T s)
{
    while (s != parent[s])
    {
        s = parent[s];
    }
    return s;
}

template<class T>
void QuickUnion<T>::print()
{
    for (T i = 0; i < size; i++)
        std::cout << '[' << i << ',' << root(i) << ']' << ' ';
    std::cout << std::endl;
}

template class QuickUnion<short>;
