#pragma once
#include "Person.h"
#include "Ticket.h"
#include "RailPass.h"
class Ticket;
class InteractablePerson :
    public Person
{

public:
    void interact(Player p);
    bool verdictChecker(bool _PlayerVerdict);
    Ticket getTicket();
    RailPass getRailPass();
protected:

    //data members
    bool _PredeterminedPassType;
    bool _PredetermindedVerdict;
    int _ScytheUse; //for unwilling passengers only 

private:
    Ticket _Ticket;
    RailPass _RailPass;
};

