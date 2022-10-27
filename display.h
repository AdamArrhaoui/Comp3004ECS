#ifndef DISPLAY_H
#define DISPLAY_H

#include <QObject>

#include "elevator.h"


class Elevator;

class Display: public QObject
{
    Q_OBJECT
public:
    Display(Elevator* elevator);
    void update(int floorNum);
private:
    int m_displayVal = 0;
    Elevator* m_elevator;
};

#endif // DISPLAY_H
