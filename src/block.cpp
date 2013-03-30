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
    &_gnd,
    &_vcc,
    &_nand_2,
    &_nor_2,
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

bool _gnd(const States in, States out)
{
    Q_UNUSED(in)
    Q_UNUSED(out)
    return true;
}

bool _vcc(const States in, States out)
{
    Q_UNUSED(in)
    Q_UNUSED(out)
    return true;
}

bool _nand_2(const States in, States out)
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

bool _nor_2(const States in, States out)
{
    if (in[0] == State::high || in[1] == State::high)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _and_2(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low)
    {
        out[0] = State::low;
        return true;
    }
    if (in[0] == State::high)
    {
        out[0] = in[1];

        //return false if in[1] != State::high
        return in[1] == State::high;
    }
    out[0] = State::undefined;
    return false;
}

/*
bool nand3(State* s)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low)
        out[0] = State::high;
    else if (in[0] == State::undefined || in[1] == State::undefined || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::low;
    return true;
}


bool nor3(State* s)
{
    if (in[0] == State::high || in[1] == State::high || in[2] == State::high)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}


//Not Logic
bool not(State* s)
{
    if (in[0] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else if (in[0] == State::high)
        out[0] = State::low;
    else
        out[0] = State::high;
    return true;
}


//And Logic

bool and3(State* s)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}


//Or Logic
bool or2(State* s)
{
    if (in[0] == State::high || in[1] == State::high)
    {
        out[0] = State::high;
        return true;
    }
    if (in[0] == State::low)
    {
        out[0] = in[1];

        //return false if in[1] != State::high
        return in[1] == State::low;
    }
    out[0] = State::undefined;
    return false;
}

bool or3(State* s)
{
    if (in[0] == State::high || in[1] == State::high || in[2] == State::high)
        out[0] = State::high;
    else if (in[0] == State::undefined || in[1] == State::undefined || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::low;
    return true;
}
*/

} //namespace Block
