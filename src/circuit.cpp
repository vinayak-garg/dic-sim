#include "cell.h"
#include "wire.h"
#include "block.h"
#include "state.h"
#include "circuit.h"
#include "constants.h"
#include "breadboard.h"
#include "quickunion.h"

#include <QtGui>

Circuit::Circuit(Console *_console) : console(_console),
    terminals(kMaxTerminals + 10), outLedList(10)
{
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
            }
            else
                wire->markRedundent(true);
        }
        else if ((led = dynamic_cast<LED *>(*it)))
        {
            if (led->col >= 0 && led->col < 10)
                outLedList[led->col] = led;
            else
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

bool Circuit::prepareConnections(bool checkGND_VCC)
{
    /*
     * Connect ICs and check for GND and VCC
     */
    int GNDid = Block::mapBlockID("GND");
    int VCCid = Block::mapBlockID("VCC");
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
            if (checkGND_VCC)
            {
                if (bd.id == GNDid && terminals.getstate(bd.outPin[0]) != State::low)
                    return false;
                else if (bd.id == VCCid && terminals.getstate(bd.outPin[0]) != State::high)
                    return false;
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

bool Circuit::run(std::vector<State> inputStates)
{
    using namespace Block;
    std::vector<State> blockInput(MAX_INPUTS), blockOutput(MAX_OUTPUTS);
    bool unsteady = true;

    //Set Toggle Buttons State
    for (size_t i = 0; i < inputStates.size(); i++)
    {
        terminals.setstate(INPUT_OFFSET + i, inputStates[i]);
        terminals.setstate(OUTPUT_OFFSET + i, State::undefined);
    }

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

    for (size_t i = 0; i < outLedList.size(); i++)
    {
        if (terminals.getstate(OUTPUT_OFFSET+i) == State::high)
            outLedList[i]->switchOn(STATE);
        else
            outLedList[i]->switchOff(STATE);
    }

    return true;
}

void Circuit::stop()
{
    for (auto led : ledList)
    {
        led->switchOff(POWER);
    }
    for (auto led : outLedList)
    {
        led->switchOff(POWER);
    }
}
