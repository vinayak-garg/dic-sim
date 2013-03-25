#include "block.h"

#include <QtCore>

namespace Block
{

std::map<std::string, int> blockIDMap;

void init()
{
    int i = 1;
    blockIDMap["GND"]    = i++;
    blockIDMap["VCC"]    = i++;
    blockIDMap["NAND2"]  = i++;
    blockIDMap["NOR2"]   = i++;
    blockIDMap["AND2"]   = i++;
    blockIDMap["OR2"]    = i++;
    blockIDMap["NOT"]    = i++;
    blockIDMap["NAND3"]  = i++;
    blockIDMap["NOR3"]   = i++;
    blockIDMap["AND3"]   = i++;
    blockIDMap["OR3"]    = i++;
}

processFn blockFn[] = {
    0,
    &_nand2,
    &_nand2,
    &_nand2,
};

int mapBlockID(std::string func)
{
    if (blockIDMap.count(func))
    {
        return blockIDMap[func];
    }
    else
    {
        qFatal("Unknown block (function) : %s", func.c_str());
        return 0;
    }
}

bool process(int blockID, const States in, States out)
{
    return blockFn[blockID](in, out);
}

bool _nand2(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low)
        out[0] = State::high;
    else if (in[0] == State::undefined || in[1] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::low;

    return true;
}

} //namespace Block
