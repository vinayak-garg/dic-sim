#include "cell.h"
#include "wire.h"
#include "block.h"
#include "state.h"
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

Circuit::Circuit(Console *_console) : console(_console), terminals(kMaxTerminals)
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
            i = _console->getOffset(wire->line().p1());
            j = _console->getOffset(wire->line().p2());
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
            led->switchOn(POWER);
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
            for (size_t i = 0; i < bd.inPin.size(); i++)
            {
                bd.inPin[i] = mapICpinToCircuit(bd.inPin[i], l, index);
            }
            for (size_t i = 0; i < bd.outPin.size(); i++)
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
        for (size_t i = 0; i < b.inPin.size(); i++)
            std::cout << b.inPin[i] << ' ';
        std::cout << std::endl;
    }
#endif
    return true;
}

bool Circuit::run()
{
    using namespace Block;
    std::vector<State> blockInput(MAX_INPUTS), blockOutput(MAX_OUTPUTS);
    bool unsteady = true;

    for (int max_iter = blocks.size(); max_iter && unsteady; max_iter--)
    {
        unsteady = false;
        for (auto b : blocks)
        {
            //Create copy of input
            for (size_t i = 0; i < b.inPin.size(); i++)
                blockInput[i] = terminals.getstate(b.inPin[i]);

            //Process!!
            if (!process(b.id, blockInput, blockOutput))
                unsteady = true;

            //Set output
            for (size_t i = 0; i < b.outPin.size(); i++)
                terminals.setstate(b.outPin[i], blockOutput[i]);
        }
    }

    for (auto led : ledList)
    {
        int i = console->getOffset(led->line().p1());
        int j = console->getOffset(led->line().p2());
        if (terminals.getstate(i) == State::undefined ||
                terminals.getstate(j) == State::undefined)
            //Raise error : TODO
            led->switchOff(STATE);
        else if (terminals.getstate(i) != terminals.getstate(j))
            led->switchOn(STATE);
        else
            led->switchOff(STATE);
    }

    return true;
}

void Circuit::stop()
{
    for (auto led : ledList)
    {
        led->switchOff(POWER);
    }
}
