#include "door.h"

Door::Door(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{}

void Door::open()
{
    switch (m_state) {
    case Closed: case Closing:
        m_state = Opening;
        break;
    case Opening:
        if(m_openAmount < 1.0){
            m_openAmount += s_doorSpeed;
        } else {
            m_openAmount = 1.0;
            m_state = Open;
        }
        break;
    default:
        break;
    }
}

void Door::close()
{

}

void Door::ringBell()
{

}
