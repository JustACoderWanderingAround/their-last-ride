#pragma once
#include "Passenger.h"
class NonInteractivePassenger :
    public Passenger
{
    void interact();


private:
    int _NonInteractiveReply;
};