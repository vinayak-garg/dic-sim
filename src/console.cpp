#include "breadboard.h"
#include "inputcell.h"
#include "constants.h"
#include "console.h"
#include "cell.h"
#include "wire.h"
#include "tag.h"
#include "led.h"
#include "ic.h"

#include <QtGui>
#include <QDebug>

Console::Console(QWidget *parent) :
    QGraphicsScene(0, 0, CONSOLE_WIDTH, CONSOLE_HEIGHT, parent),
    toggleInputStates(10)
{
    powerButton = new PowerButton(780, 20);
    addItem(powerButton);
    power = false;

    mode = Mode::inserting_wire;
    isFirstPoint = true;
    lastCell = nullptr;
    lastInputCell = nullptr;

    addBreadboard();

    for (int i = 0; i < IO_COUNT; i++)
    {
        addItem(new LED(QPointF(35 + i*70, 30), QPointF(35 + i*70, 30), i));
        addItem(new InputCell(30 + i*70, 50, 8, 8, 0, OUTPUT_OFFSET + i));

        toggleButtons.append(new ToggleButton(20 + i*70, 590, i));
        addItem(toggleButtons.back());
        addItem(new InputCell(30 + i*70, 570, 8, 8, 0, INPUT_OFFSET + i));

        toggleInputStates[i] = State::low;

        inputTags.append(nullptr);
        outputTags.append(nullptr);
    }
}

void Console::togglePower()
{
    power = !power;
    powerButton->set(power);
}

void Console::toggleInput(int i)
{
    togglebuttonMouseEvent(toggleButtons[i]);
}

void Console::addTag(bool io, int number, QString text)
{
    number--;
    if (io)
    {
        if (inputTags[number])
            inputTags[number]->setText(text);
        else
            addItem(inputTags[number] = new Tag(48 + number*70, 575, text));
    }
    else
    {
        if (outputTags[number])
            outputTags[number]->setText(text);
        else
            addItem(outputTags[number] = new Tag(48 + number*70, 30, text));
    }
}

QString Console::getTag(bool io, int number)
{
    number--;
    if (io)
    {
        if (inputTags[number])
            return inputTags[number]->getText();
        else
            return QString("I") + QString::number(number);
    }
    else
    {
        if (outputTags[number])
            return outputTags[number]->getText();
        else
            return QString("O") + QString::number(number);
    }
}

void Console::addBreadboard()
{
    addItem(new Breadboard(kLeft, kTop));

    highlightColor.setRgb(0, 200, 0);
    selectedTColor.setRgb(255, 200, 0);
    selectedBColor.setRgb(240, 200, 0);
    terminalColor.setRgb(180, 180, 180);
    borderColor.setRgb(80, 80, 80);
    backgroundColor.setRgb(254, 252, 250);

    int x = kOuterBorder + kLeft, i, j;

    for (i = 0; i < kCols; x += kBox, ++i)
    {
        for (j = 0; j < 5; ++j)
        {
            addItem(new Cell(x, ktR1 + j*kBox, kSquare, kSquare, j, i));
            addItem(new Cell(x, ktR2 + j*kBox, kSquare, kSquare, 5 + j, i));
            addItem(new Cell(x, ktR3 + j*kBox, kSquare, kSquare, 10 + j, i));
            addItem(new Cell(x, ktR4 + j*kBox, kSquare, kSquare, 15 + j, i));
            addItem(new Cell(x, ktR5 + j*kBox, kSquare, kSquare, 20 + j, i));
            addItem(new Cell(x, ktR6 + j*kBox, kSquare, kSquare, 25 + j, i));
        }
    }

    //Bus Contacts
    for (i = 0, x = kOuterBorder + kLeft; i < kBusCols; x+=kBusGap, i++)
    {
        for (j = 0; j < 5; x+=kBox, j++)
        {
            addItem(new Cell(x, kbR1, kSquare, kSquare, BUS_ROW_HIGH, BUS_COL));
            addItem(new Cell(x, kbR1 + kBox, kSquare, kSquare, BUS_ROW_LOW, BUS_COL));
            addItem(new Cell(x, kbR2, kSquare, kSquare, BUS_ROW_HIGH, BUS_COL));
            addItem(new Cell(x, kbR2 + kBox, kSquare, kSquare, BUS_ROW_LOW, BUS_COL));
        }
    }
}

void Console::setWireColor(QColor color)
{
    wireColor = color;
}

void Console::setIC(QString name, int l, std::vector<BlockData> blocks)
{
    curICName = name;
    curICpins = l;
    curICblocks = blocks;
}

int Console::getOffset(QPointF p)
{
    auto allItems = this->items(p);
    Cell *cell;
    InputCell *inputCell;
    for (auto it = allItems.begin(); it != allItems.end(); it++)
    {
        if ((cell = dynamic_cast<Cell *>(*it)))
        {
            if (cell->row() == BUS_ROW_HIGH)
                return HIGH_OFFSET;
            else if (cell->row() == BUS_ROW_LOW)
                return LOW_OFFSET;
            else
                return (cell->row()/5)*kCols + cell->col();
        }
        else if ((inputCell = dynamic_cast<InputCell *>(*it)))
        {
            return inputCell->col();
        }
    }
    return -1;
}

void Console::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QList<QGraphicsItem *> topItemsList = items(event->scenePos());
    Cell *cellItem = nullptr;
    InputCell *inputCellItem = nullptr;
    ToggleButton *toggleButtonItem = nullptr;

    for (auto it = topItemsList.begin(); it != topItemsList.end(); it++)
    {
        if ((cellItem = dynamic_cast<Cell *>(*it)))
        {
            if (!power)
                cellMouseEvent(cellItem);
            else
                QMessageBox::warning(0, "Error", "Cannot edit circuit while power is on.");
            break;
        }
        else if ((inputCellItem = dynamic_cast<InputCell *>(*it)))
        {
            if (!power)
                inputCellMouseEvent(inputCellItem);
            else
                QMessageBox::warning(0, "Error", "Cannot edit circuit while power is on.");
            break;
        }
        else if ((toggleButtonItem = dynamic_cast<ToggleButton *>(*it)))
        {
            togglebuttonMouseEvent(toggleButtonItem);
            emit inputToggled();
            break;
        }
        else if (dynamic_cast<PowerButton *>(*it))
        {
            emit powerToggled();
            break;
        }
    }
}

void Console::cellMouseEvent(Cell *cell)
{
    QPointF mousePos(cell->scenePos().x() + (kSquare>>1),
                     cell->pos().y() + (kSquare>>1));

    if (cell->isOccupied())
    {
        if (mode == Mode::inserting_wire || mode == Mode::inserting_led)
        {
            if (isFirstPoint)
            {
                auto collItems = cell->collidingItems();
                for (auto it = collItems.begin(); it != collItems.end(); it++)
                {
                    if (mode == Mode::inserting_wire && dynamic_cast<Wire *>(*it))
                    {
                        Wire *wire = dynamic_cast<Wire *>(*it);
                        QLineF line = wire->line();
                        if (line.p1() == mousePos)
                            lastMousePos = line.p2();
                        else
                            lastMousePos = line.p1();
                        removeItem(wire);
                        cell->unoccupy();
                        lastInputCell = nullptr;
                        isFirstPoint = false;
                    }
                }
            }
            else if (mousePos == lastMousePos)
            {
                cell->unoccupy();
                isFirstPoint = true;
            }
        }
        return;
    }

    cell->setBrush(Qt::yellow);

    if (mode == Mode::inserting_ic)
    {
        if (cell->isCenter())
        {
            IC *ic = new IC(curICName, curICpins/2, mousePos, cell->index(), curICblocks);
            Cell *cell;
            int freeCells = 0;
            addItem(ic);
            auto collCells = ic->collidingItems();
            for (auto it = collCells.begin(); it != collCells.end(); it++)
            {
                if ((cell = dynamic_cast<Cell *>(*it)))
                {
                    if (cell->isOccupied())
                        break;
                    else
                        freeCells++;
                }
            }
            if (freeCells != curICpins)
                removeItem(ic);
            else
            {
                for (auto it = collCells.begin(); it != collCells.end(); it++)
                {
                    if ((cell = dynamic_cast<Cell *>(*it)))
                        cell->occupy();
                }
            }
        }
    }
    else if (isFirstPoint)
    {
        cell->occupy();
        lastMousePos = mousePos;
        lastCell = cell;
        lastInputCell = nullptr;
    }
    else
    {
        if (mode == Mode::inserting_wire)
        {
            cell->occupy();
            addItem(new Wire(lastMousePos, mousePos, wireColor));
        }
        else if (mode == Mode::inserting_led)
        {
            if (LED::validDistance(lastMousePos, mousePos))
            {
                cell->occupy();
                addItem(new LED(lastMousePos, mousePos));
            }
            else
            {
                QMessageBox::warning(0, "Error", "LED end points need to be closer");
                lastCell->unoccupy();
            }
        }
    }
    isFirstPoint = !isFirstPoint;
}

void Console::inputCellMouseEvent(InputCell *cell)
{
    if (mode == Mode::inserting_led || mode == Mode::inserting_ic)
    {
        return;
    }

    QPointF mousePos(cell->scenePos().x() + (kSquare>>1),
                     cell->pos().y() + (kSquare>>1));

    if (cell->isOccupied())
    {
        if (isFirstPoint)
        {
            auto collItems = cell->collidingItems();
            for (auto it = collItems.begin(); it != collItems.end(); it++)
            {
                Wire *wire;
                if ((wire = dynamic_cast<Wire *>(*it)))
                {
                    QLineF line = wire->line();
                    if (line.p1() == mousePos)
                        lastMousePos = line.p2();
                    else
                        lastMousePos = line.p1();
                    removeItem(wire);
                    cell->unoccupy();
                    isFirstPoint = false;
                }
            }
        }
        else if (mousePos == lastMousePos)
        {
            cell->unoccupy();
            isFirstPoint = true;
        }
        return;
    }

    cell->setBrush(Qt::yellow);

    if (isFirstPoint)
    {
        cell->occupy();
        lastMousePos = mousePos;
        lastCell = nullptr;
        lastInputCell = cell;
    }
    else
    {
        if (lastInputCell != nullptr)
            return;
        cell->occupy();
        addItem(new Wire(lastMousePos, mousePos, wireColor));
    }
    isFirstPoint = !isFirstPoint;
}

void Console::togglebuttonMouseEvent(ToggleButton *toggleButton)
{
    if (toggleButton->isOn())
    {
        toggleButton->set(false);
        toggleInputStates[toggleButton->id] = State::low;
    }
    else
    {
        toggleButton->set(true);
        toggleInputStates[toggleButton->id] = State::high;
    }
}

typedef qint8 ItemType;

namespace Item
{
    const ItemType WIRE = 1;
    const ItemType IC   = 2;
    const ItemType LED  = 3;
    const ItemType TAG  = 4;
    const ItemType END  = 99;
}

void Console::writeWire(QDataStream &out, const Wire &wire) const
{
    out << Item::WIRE;
    QLineF line = wire.line();
    out << line.p1().x() << line.p1().y() << line.p2().x() << line.p2().y();
    QColor col = wire.pen().color();
    out << col.red() << col.green() << col.blue();
}

void Console::readWire(QDataStream &in)
{
    QLineF line;
    QColor col;

    qreal x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;
    line.setPoints(QPointF(x1, y1), QPointF(x2, y2));
    QGraphicsItem* item = this->itemAt(x1, y1);
    Cell *cell;
    InputCell *inputCell;
    if ((cell = dynamic_cast<Cell *>(item)))
        cell->occupy();
    else if ((inputCell = dynamic_cast<InputCell *>(item)))
        inputCell->occupy();
    item = this->itemAt(x2, y2);
    if ((cell = dynamic_cast<Cell *>(item)))
        cell->occupy();
    else if ((inputCell = dynamic_cast<InputCell *>(item)))
        inputCell->occupy();

    int r, g, b;
    in >> r >> g >> b;
    col.setRgb(r, g, b);

    addItem(new Wire(line.p1(), line.p2(), col));
}

void Console::writeLED(QDataStream &out, const LED &led) const
{
    if (led.col >= 0 && led.col < 10)
        return;
    out << Item::LED;

    QLineF line = led.line();
    out << line.p1().x() << line.p1().y() << line.p2().x() << line.p2().y();
}

void Console::readLED(QDataStream &in)
{
    QLineF line;

    qreal x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;
    line.setPoints(QPointF(x1, y1), QPointF(x2, y2));
    QGraphicsItem* item = this->itemAt(x1, y1);
    Cell *cell;
    if ((cell = dynamic_cast<Cell *>(item)))
        cell->occupy();
    item = this->itemAt(x2, y2);
    if ((cell = dynamic_cast<Cell *>(item)))
        cell->occupy();

    addItem(new LED(line.p1(), line.p2()));
}

void Console::writeIC(QDataStream &out, const IC &ic) const
{
    out << Item::IC;

    out << ic.name << ic.l << ic.index << ic.x << ic.y;
    out << (qint32)ic.blocks.size();
    for (auto block : ic.blocks)
    {
        out << block.id;
        out << (qint32)block.inPin.size();
        for (auto pin : block.inPin)
            out << pin;
        out << (qint32)block.outPin.size();
        for (auto pin : block.outPin)
            out << pin;
    }
}

void Console::readIC(QDataStream &in)
{
    int l, index, val;
    QString name;
    qreal x, y;
    in >> name >> l >> index >> x >> y;

    std::vector<BlockData> blocks;
    BlockData block;
    qint32 size1, size2;
    in >> size1;
    for (int i = 0; i < size1; i++)
    {
        in >> block.id;
        in >> size2;
        for (int j = 0; j < size2; j++)
        {
            in >> val;
            block.inPin.push_back(val);
        }
        in >> size2;
        block.outPin.reserve(size2);
        for (int j = 0; j < size2; j++)
        {
            in >> val;
            block.outPin.push_back(val);
        }
        blocks.push_back(block);
        block.inPin.clear();
        block.outPin.clear();
    }

    addItem(new IC(name, l, x, y, index, blocks));
}

void Console::writeTag(QDataStream &out, const Tag &tag) const
{
    out << Item::TAG;
    bool io = tag.y > 300;
    int number = (tag.x + 22)/70;
    out << io << number << tag.text;
}

void Console::readTag(QDataStream &in)
{
    bool io;
    int number;
    QString text;

    in >> io >> number >> text;
    addTag(io, number, text);
}

QDataStream &operator<<(QDataStream &out, const Console &console)
{
    auto items = console.items();
    Wire *wire;
    LED *led;
    IC *ic;
    Tag *tag;
    foreach (QGraphicsItem *item, items)
    {
        if ((wire = dynamic_cast<Wire *>(item)))
            console.writeWire(out, *wire);
        else if ((led = dynamic_cast<LED *>(item)))
            console.writeLED(out, *led);
        else if ((ic = dynamic_cast<IC *>(item)))
            console.writeIC(out, *ic);
        else if ((tag = dynamic_cast<Tag *>(item)))
            console.writeTag(out, *tag);
    }
    out << Item::END;

    return out;
}

QDataStream &operator>>(QDataStream &in, Console &console)
{
    ItemType it;
    in >> it;
    while (it != Item::END)
    {
        switch (it)
        {
        case Item::WIRE:
            console.readWire(in);
            break;
        case Item::LED:
            console.readLED(in);
            break;
        case Item::IC:
            console.readIC(in);
            break;
        case Item::TAG:
            console.readTag(in);
            break;
        }

        in >> it;
    }
    return in;
}

