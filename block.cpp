#include "block.h"

#include <QtCore>

std::map<std::string, int> Block::blockIDMap;

Block::Block()
{
}

void Block::init()
{
    int i = 1;
    blockIDMap["GND"] = i++;
    blockIDMap["VCC"] = i++;
    blockIDMap["NAND2"] = i++;
    blockIDMap["NOR2"] = i++;
    blockIDMap["AND2"] = i++;
    blockIDMap["OR2"] = i++;
    blockIDMap["NOT"] = i++;
    blockIDMap["NAND3"] = i++;
    blockIDMap["NOR3"] = i++;
    blockIDMap["AND3"] = i++;
    blockIDMap["OR3"] = i++;
}

int Block::mapBlockID(std::string func)
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
