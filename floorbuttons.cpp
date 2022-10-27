#include "floorbuttons.h"

FloorButtons::FloorButtons(Floor* floor)
    :QObject(floor), m_floor(floor)
{}
