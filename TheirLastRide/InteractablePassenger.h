#pragma once
#include "Passenger.h"
#include "Ticket.h"
class Ticket;
class InteractablePassenger :
    public Passenger
{

public:
protected:

    //data members
    int _PredetermindedVerdict;
    int _Verdict; //player's verdict of whether passenger is dead or alive
    int _ScytheUse; //for unwilling passengers only 

private:
    Ticket _ticket;
};

