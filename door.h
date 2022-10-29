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
    enum DoorState {Open, Opening, Closing, Closed};
    void open();
    void close();
    void ringBell();

private:
    Elevator* m_elevator;
    float m_openAmount = 0;
    DoorState m_state = Closed;
    static float s_doorSpeed = 0.1;
};

#endif // DOOR_H
