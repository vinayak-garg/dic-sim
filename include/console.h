#ifndef CONSOLE_H
#define CONSOLE_H

#include "ic.h"
#include "led.h"
#include "wire.h"
#include "cell.h"
#include "powerbutton.h"
#include "togglebutton.h"
#include <QtGui>

enum class Mode : qint8
{
    inserting_wire,
    inserting_led,
    inserting_ic
};

class Console : public QGraphicsScene
{
    Q_OBJECT

    friend QDataStream &operator<<(QDataStream &out, const Console &console);
    friend QDataStream &operator>>(QDataStream &in, Console &console);
public:
    explicit Console(QWidget *parent = 0);
    void setWireColor(QColor color);
    void setIC(QString name, int l);
    int getOffset(QPointF p);
    void togglePower();

    static const int CONSOLE_WIDTH = 900;
    static const int CONSOLE_HEIGHT = 640;

signals:
    void powerToggled();

public slots:
    void setMode(Mode _mode)
    {
        mode = _mode;
        isFirstPoint = true;
        lastMousePos = QPointF();
    }

protected:
    void addBreadboard();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void cellMouseEvent(Cell* cell);
    void togglebuttonMouseEvent(ToggleButton* toggleButton);

private:
    void writeWire(QDataStream &out, const Wire &wire) const;
    void readWire(QDataStream &in);
    void writeLED(QDataStream &out, const LED &led) const;
    void readLED(QDataStream &in);

    bool isFirstPoint;
    Mode mode;

    QPointF lastMousePos;
    Cell *lastCell;

    QString curICName;
    int curICpins;

    bool power;
    PowerButton *powerButton;
    QList<ToggleButton *> toggleButtons;

    QColor highlightColor;
    QColor selectedTColor;
    QColor selectedBColor;
    QColor terminalColor;
    QColor busColor;
    QColor borderColor;
    QColor backgroundColor;

    QColor wireColor;
};

#endif // CONSOLE_H
