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

    bool _gnd(const States in, States out);
    bool _vcc(const States in, States out);
    bool _nand_2(const States in, States out);
    bool _nand_3(const States in, States out);
    bool _nor_2(const States in, States out);
    bool _nor_3(const States in, States out);
    bool _nor_4(const States in, States out);
    bool _nor_5(const States in, States out);
    bool _and_2(const States in, States out);
    bool _and_3(const States in, States out);
    bool _and_4(const States in, States out);
    bool _and_5(const States in, States out);
    bool _or_2(const States in, States out);
    bool _not(const States in, States out);
    bool _xor_2(const States in, States out);
    bool _nand_4(const States in, States out);
    bool _nand_5(const States in, States out);
    bool _and_6(const States in, States out);
    bool _or_3(const States in, States out);
    bool _or_4(const States in, States out);

    bool process(int blockID, const States in, States out);
}

#endif // BLOCK_H
