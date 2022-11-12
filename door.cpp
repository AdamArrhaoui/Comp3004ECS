#include <QDebug>

#include "door.h"

Door::Door(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{
    connect(m_elevator, SIGNAL(updated()), this, SLOT(update()));
}

void Door::update()
{
    switch (m_state) {
    case Closed:
        break;
    case Closing:
        qDebug() << "Closing door:" << m_openAmount;
        m_openAmount -= s_doorSpeed;
        if(m_openAmount <= 0) {
            m_openAmount = 0;
            m_state = Closed;
            qDebug() << "Door is closed!";
        }
        break;
    case Opening:
        qDebug() << "Opening door:" << m_openAmount;
        m_openAmount += s_doorSpeed;
        if(m_openAmount >= 1.0) {
            m_openAmount = 1.0;
            m_state = Open;
            qDebug() << "Door is open!";
        }
        break;
    case Open:
        qDebug() << "Door closing in" << s_maxOpenTime - m_currOpenTime;
        ++m_currOpenTime;
        if(m_currOpenTime >= s_maxOpenTime){
            close();
        }
        break;
    default:
        break;
    }
}

void Door::open()
{
    // Door is already open, reset door timer
    if(m_state == Open){
        m_currOpenTime = 0;
        return;
    }
    m_state = Opening;
}

void Door::close()
{
    if(m_state == Closed or m_state == Closing){
        return;
    }
    m_currOpenTime = 0;
    m_state = Closing;
}

void Door::ringBell()
{
    qInfo() << "Ding Dong!";
}

Door::DoorState Door::state() const
{
    return m_state;
}

