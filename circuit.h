#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "console.h"
#include "quickunion.h"

//#include <vector>

class Circuit
{
public:
    Circuit(Console *console);
    bool checkConnections();
    bool run();
private:
    QuickUnion<short> terminals;
};

#endif // CIRCUIT_H
