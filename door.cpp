#include "door.h"

Door::Door(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{}
