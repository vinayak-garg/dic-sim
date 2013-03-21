#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "led.h"
#include "blockdata.h"
#include "console.h"
#include "quickunion.h"

#include <vector>

struct Connection;

class Circuit
{
public:
    Circuit(Console *console);
    bool checkConnections();
    bool run();
    void stop();
private:
    std::vector<std::vector<BlockData> > *ICDataListPtr;
    QuickUnion terminals;
    std::vector<Connection> connections;
    std::vector<LED *> leds;
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
