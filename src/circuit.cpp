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
    IC *ic;
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
                //usedTerminals[i]
            }
            else
                wire->markRedundent(true);
        }
        else if ((led = dynamic_cast<LED *>(*it)))
        {
            ledList.push_back(led);
            led->switchOn(POWER | STATE);
        }
        else if ((ic = dynamic_cast<IC *>(*it)))
        {
            icList.push_back(ic);
        }
    }
#ifdef QT_DEBUG
    terminals.print();
#endif
}

bool Circuit::prepareConnections()
{
    /*
     * Connect ICs
     */
    for (auto ic : icList)
    {
        int l = ic->length();
        int index = ic->getindex();
        for (auto block : ic->blocks)
        {
            BlockData bd = block;
            for (int i = 0; i < bd.inPin.size(); i++)
            {
                bd.inPin[i] = mapICpinToCircuit(bd.inPin[i], l, index);
            }
            for (int i = 0; i < bd.outPin.size(); i++)
            {
                bd.outPin[i] = mapICpinToCircuit(bd.outPin[i], l, index);
            }
            blocks.push_back(bd);
        }
    }
#ifdef QT_DEBUG
    for (auto b : blocks)
    {
        std::cout << b.id << '\n';
        for (int i = 0; i < b.inPin.size(); i++)
            std::cout << b.inPin[i] << ' ';
        std::cout << std::endl;
    }
#endif
    return true;
}

bool Circuit::run()
{
    return true;
}

void Circuit::stop()
{
    for (auto led : ledList)
    {
        led->switchOff(POWER);
    }
}
