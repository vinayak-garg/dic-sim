#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <map>

class Block
{
public:
    Block();
    static void init();
    static int mapBlockID(std::string func);
    std::vector<short> inputs, outputs;
private:
    static std::map<std::string, int> blockIDMap;
    int blockID;
};

#endif // BLOCK_H
