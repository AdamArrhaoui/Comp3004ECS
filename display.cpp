#include "display.h"

Display::Display(Elevator* elevator)
    : QObject(elevator)
    , m_elevator(elevator)
{}

void Display::update(int floorNum)
{
    m_displayVal = floorNum;

}
