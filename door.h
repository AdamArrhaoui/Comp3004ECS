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

    DoorState state() const;

public slots:
    void update();

private:
    Elevator* m_elevator;
    float m_openAmount = 0;
    float m_currOpenTime = 0;
    DoorState m_state = Closed;
    static constexpr float s_doorSpeed = 0.25;
    static constexpr int s_maxOpenTime = 5;
};

#endif // DOOR_H
