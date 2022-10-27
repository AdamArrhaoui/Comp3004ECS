#include "buttonpanel.h"

ButtonPanel::ButtonPanel(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{}

void ButtonPanel::pressDestButton(int floorNum)
{

}

void ButtonPanel::unpressDestButton(int floorNum)
{

}

void ButtonPanel::pressCloseDoor()
{

}

void ButtonPanel::holdOpenDoor()
{

}

void ButtonPanel::releaseOpenDoor()
{

}

void ButtonPanel::pressEmergencyButton()
{

}
