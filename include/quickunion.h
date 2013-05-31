#ifndef QUICKUNION_H
#define QUICKUNION_H

#include <vector>
#include <iostream>
#include "state.h"

class QuickUnion
{
public:
    explicit QuickUnion(size_t _size);
    ~QuickUnion()
    {}
    bool join(int a, int b);
    int root(int a);
    State getstate(int a)
    {
        return state[root(a)];
    }
    void setstate(int a, State s)
    {
        //state[a] = s;
        _setFixedState(a, s);
    }
    void print();

private:
    void _setFixedState(int a, State s)
    {
        int rootA = root(a);
        //if (state[rootA] != State::high)
            state[rootA] = s;
    }

    std::vector<int> parent;
    std::vector<State> state;
    int size;
};

#endif // QUICKUNION_H
