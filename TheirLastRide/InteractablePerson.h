#pragma once
#include "Person.h"
#include "Ticket.h"
#include "RailPass.h"
class Ticket;
class InteractablePerson :
    public Person
{

public:
    InteractablePerson();
    bool loadNodes();
    InteractablePerson(std::string name, bool passType, bool verdict, Ticket* ticket, RailPass* railpass);
    void interact(Player p);
    bool verdictChecker(bool _PlayerVerdict);
    Ticket getTicket();
    RailPass getRailPass();
    std::string getName();
    bool getPassType();
protected:

    //data members
    bool _PredeterminedPassType;
    bool _PredetermindedVerdict;
    bool _PassType;
    int _ScytheUse; //for unwilling passengers only 

private:
    Ticket _Ticket;
    RailPass _RailPass;
    std::string _name;
};

