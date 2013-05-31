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
    blockIDMap["NAND3"]  = i++;
    blockIDMap["NOR2"]   = i++;
    blockIDMap["NOR3"]   = i++;
    blockIDMap["NOR4"]   = i++;
    blockIDMap["NOR5"]   = i++;
    blockIDMap["AND2"]   = i++;
    blockIDMap["AND3"]   = i++;
    blockIDMap["AND4"]   = i++;
    blockIDMap["AND5"]   = i++;
    blockIDMap["OR2"]    = i++;
    blockIDMap["NOT"]    = i++;
    blockIDMap["XOR2"]   = i++;
    blockIDMap["NAND4"]  = i++;
    blockIDMap["NAND5"]  = i++;
    blockIDMap["AND6"]   = i++;
}

processFn blockFn[] = {
    0,
    &_gnd,
    &_vcc,
    &_nand_2,
    &_nand_3,
    &_nor_2,
    &_nor_3,
    &_nor_4,
    &_nor_5,
    &_and_2,
    &_and_3,
    &_and_4,
    &_and_5,
    &_or_2,
    &_not,
    &_xor_2,
    &_nand_4,
    &_nand_5,
    &_and_6,
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

bool _nand_3(const States in, States out)
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

bool _nand_4(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low
             || in[3] == State::low)
        out[0] = State::high;
    else if (in[0] == State::undefined || in[1] == State::undefined
              || in[2] == State::undefined || in[3] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::low;
    return true;
}

bool _nand_5(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low
             || in[3] == State::low || in[4] == State::low)
        out[0] = State::high;
    else if (in[0] == State::undefined || in[1] == State::undefined
              || in[2] == State::undefined || in[3] == State::undefined
              || in[4] == State::undefined)
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

bool _nor_3(const States in, States out)
{
    if (in[0] == State::high || in[1] == State::high || in[2] == State::high)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _nor_4(const States in, States out)
{
    if (in[0] == State::high || in[1] == State::high || in[2] == State::high
            || in[3] == State::high)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined || in[3] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _nor_5(const States in, States out)
{
    if (in[0] == State::high || in[1] == State::high || in[2] == State::high
            || in[3] == State::high || in[4] == State::high)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined || in[3] == State::undefined
             || in[4] == State::undefined)
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

bool _and_3(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _and_4(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low
            || in[3] == State::low)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined || in[3] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _and_5(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low
            || in[3] == State::low || in[4] == State::low)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined || in[3] == State::undefined
             || in[4] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _and_6(const States in, States out)
{
    if (in[0] == State::low || in[1] == State::low || in[2] == State::low
            || in[3] == State::low || in[4] == State::low|| in[5] == State::low)
        out[0] = State::low;
    else if (in[0] == State::undefined || in[1] == State::undefined
             || in[2] == State::undefined || in[3] == State::undefined
             || in[4] == State::undefined || in[5] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    else
        out[0] = State::high;
    return true;
}

bool _not(const States in, States out)
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

bool _or_2(const States in, States out)
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

bool _xor_2(const States in, States out)
{
    if (in[0] == State::undefined || in[1] == State::undefined)
    {
        out[0] = State::undefined;
        return false;
    }
    if (in[0] == in[1])
    {
        out[0] = State::low;
    }
    else
    {
        out[0] = State::high;
    }
    return true;
}

/*

bool _nor_3(const States in, States out)
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


//And Logic

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
