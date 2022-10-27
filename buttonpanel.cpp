#include "buttonpanel.h"

ButtonPanel::ButtonPanel(Elevator* elevator)
    :QObject(elevator), m_elevator(elevator)
{}

void ButtonPanel::pressDestButton(int floorNum)
{
    if(not m_pressedDestButtons.contains(floorNum)){
        m_pressedDestButtons.insert(floorNum);
        emit destButtonPressed(floorNum);
    }
}

void ButtonPanel::unpressDestButton(int floorNum)
{
    if(m_pressedDestButtons.contains(floorNum)){
        m_pressedDestButtons.remove(floorNum);
    }
}

