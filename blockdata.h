#ifndef BLOCKDATA_H
#define BLOCKDATA_H

#include <vector>

struct BlockData
{
    int id;
    std::vector<int> inPin, outPin;
    void reset()
    {
        id = 0;
        inPin.clear();
        outPin.clear();
    }
};

#endif // BLOCKDATA_H
