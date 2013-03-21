#include "cell.h"
#include "wire.h"
#include "circuit.h"
#include "breadboard.h"
#include "quickunion.h"

#include <QtGui>

#include <bitset>

const short kMaxTerminals = kCols*6
        + 10 /* Input points */
        + 10 /* Output points */;
const short INPUT_OFFSET = kCols*6;
const short OUTPUT_OFFSET = INPUT_OFFSET + 10;

Circuit::Circuit(Console *console) : terminals(kMaxTerminals)
{
    //terminals.setstate(HIGH_OFFSET, State::high);
    //terminals.setstate(LOW_OFFSET, State::low);
    for (int i = 0; i < 10; i++)
    {
        terminals.setstate(INPUT_OFFSET + i, State::low);
        terminals.setstate(OUTPUT_OFFSET + i, State::low);
    }

    QList<QGraphicsItem *> items = console->items();

    Wire *wire;
    LED *led;
    int i, j;

    for (auto it = items.begin(); it != items.end(); it++)
    {
        if ((wire = dynamic_cast<Wire *>(*it)))
        {
            i = console->getOffset(wire->line().p1());
            j = console->getOffset(wire->line().p2());
            if (terminals.join(i, j))
            {
                connections.push_back(Connection(i, j));
                wire->markRedundent(false);
            }
            else
                wire->markRedundent(true);
        }
        else if ((led = dynamic_cast<LED *>(*it)))
        {
            leds.push_back(led);
            led->switchOn(POWER | STATE);
        }
    }
#ifdef QT_DEBUG
    terminals.print();
#endif
}

void Circuit::stop()
{
    for (auto led : leds)
    {
        led->switchOff(POWER);
    }
}

bool Circuit::checkConnections()
{
    std::bitset<kMaxTerminals> usedTerminals;
    return true;
}

bool Circuit::run()
{
    return true;
}
