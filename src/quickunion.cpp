#include "quickunion.h"
#include "breadboard.h"

#include <iostream>
#include <cassert>

QuickUnion::QuickUnion(size_t _size) :
    parent(_size), state(_size, State::undefined), size(_size)
{
    for (int i = 0; i < size; i++)
        parent[i] = i;
}

bool QuickUnion::join(int a, int b)
{
    assert(a < size && b < size);
    if (a < 0 && b < 0) //Both HIGH/LOW (fixed) voltage
        return false;

    if      (a == HIGH_OFFSET) _setFixedState(b, State::high);
    else if (a == LOW_OFFSET ) _setFixedState(b, State::low);
    else if (b == HIGH_OFFSET) _setFixedState(a, State::high);
    else if (b == LOW_OFFSET ) _setFixedState(a, State::low);
    else
    {
        // a <-- b
        int rootA = root(a);
        int rootB = root(b);
        parent[rootB] = rootA;
        if (state[rootB] == State::high || state[rootA] == State::undefined)
            state[rootA] = state[rootB];
    }
    return true;
}

int QuickUnion::root(int a)
{
    while (a != parent[a])
    {
        parent[a] = parent[parent[a]]; //path compression
        a = parent[a];
    }
    return a;
}

void QuickUnion::print()
{
    for (int i = 0; i < size; i++)
        std::cout << '[' << i << ',' << root(i) << ']' << ' ';
    std::cout << std::endl;
}
