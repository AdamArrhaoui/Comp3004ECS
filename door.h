#ifndef DOOR_H
#define DOOR_H

#include <QObject>

#include "elevator.h"


class Elevator;

class Door : public QObject
{
    Q_OBJECT
public:
    Door(Elevator* elevator);
    void open();
    void close();
    void ringBell();
private:
    Elevator* m_elevator;
};

#endif // DOOR_H
