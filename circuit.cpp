#include "cell.h"
#include "wire.h"
#include "circuit.h"
#include "breadboard.h"
#include "quickunion.h"

#include <QtGui>

#include <bitset>

const short kMaxTerminals = kCols*6;

Circuit::Circuit(Console *console) : terminals(kMaxTerminals)
{
    QList<QGraphicsItem *> cellItems, items = console->items();

    Wire *wire;
    Cell *cell;
    int i, j;

    for (auto it = items.begin(); it != items.end(); it++)
    {
        if ((wire = dynamic_cast<Wire *>(*it)))
        {
            cellItems = console->items(wire->line().p1());
            for (auto it2 = cellItems.begin(); it2 != cellItems.end(); it2++)
            {
                if ((cell = dynamic_cast<Cell *>(*it2)))
                {
                    i = (cell->row()/5)*kCols + cell->col();
                    break;
                }
            }
            cellItems = console->items(wire->line().p2());
            for (auto it2 = cellItems.begin(); it2 != cellItems.end(); it2++)
            {
                if ((cell = dynamic_cast<Cell *>(*it2)))
                {
                    j = (cell->row()/5)*kCols + cell->col();
                    break;
                }
            }
            terminals.join(i, j);
        }
    }
#ifdef QT_DEBUG
    terminals.print();
#endif
}

bool Circuit::checkConnections()
{
    std::bitset<kMaxTerminals> usedTerminals;
    return true;
}
