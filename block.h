#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <map>

class Block
{
public:
    Block();
    static void init();
    static int mapBlockID(std::string func);
private:
    static std::map<std::string, int> blockIDMap;
};

#endif // BLOCK_H
