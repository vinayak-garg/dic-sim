#ifndef BLOCK_H
#define BLOCK_H

#include "state.h"

#include <string>
#include <vector>
#include <map>

namespace Block
{
    void init();
    int mapBlockID(std::string func);
    extern std::map<std::string, int> blockIDMap;

    typedef std::vector<State> &States;
    typedef bool (*processFn)(const States in, States out);

    bool _nand2(const States in, States out);
    bool _nand3(const States in, States out);

    bool process(int blockID, const States in, States out);
}

#endif // BLOCK_H
