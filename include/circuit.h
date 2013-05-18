#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "ic.h"
#include "led.h"
#include "state.h"
#include "console.h"
#include "blockdata.h"
#include "breadboard.h"
#include "quickunion.h"

#include <vector>

struct Connection;

class Circuit
{
public:
    Circuit(Console *_console);
    bool prepareConnections();
    bool run(std::vector<State> inputStates);
    void stop();
protected:
    int mapICpinToCircuit(int pin, int l, int topleftindex)
    {
        if (pin <= l)
            return topleftindex + kCols + pin-1;
        else
            return topleftindex + (l*2 - pin);
    }

private:
    Console *console;
    std::vector<std::vector<BlockData> > *ICDataListPtr;
    QuickUnion terminals;
    std::vector<bool> usedTerminals;
    std::vector<Connection> connections;
    std::vector<LED *> ledList;
    std::vector<IC *> icList;
    std::vector<BlockData> blocks;
};

struct Connection
{
    int p1, p2;
    Connection()
    {}
    Connection(int _p1, int _p2) : p1(_p1), p2(_p2)
    {}
};

#endif // CIRCUIT_H
