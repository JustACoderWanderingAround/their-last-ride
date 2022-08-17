#pragma once
#include "Passenger.h"
#include "Ticket.h"
class Ticket;
class InteractablePassenger :
    public Passenger
{

public:
    void interact();
    bool verdictChecker(bool _PlayerVerdict);
    Ticket getTicket();
protected:

    //data members
    void interact();
    bool _PredeterminedPassType;
    bool _PredetermindedVerdict;
    int _ScytheUse; //for unwilling passengers only 

private:
    Ticket _Ticket;
};

