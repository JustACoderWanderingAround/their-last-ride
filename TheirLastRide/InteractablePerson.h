#pragma once
#include "Person.h"
#include "Ticket.h"
#include "RailPass.h"
class Person;
class Ticket;
class InteractablePerson :
    public Person
{

public:
    InteractablePerson();
    bool loadNodes();
    bool loadDeathStatus();
    InteractablePerson(std::string name, bool passType, bool verdict, Ticket* ticket, RailPass* railpass);
    InteractablePerson(const std::string& name);
    bool verdictChecker(bool _PlayerVerdict);
    Ticket* getTicket();
    RailPass* getRailPass();
    std::string getName();
    bool getPassType();
    Node*& getCurrentNode();
    void setTicket(Ticket* t);
    void setRailPass(RailPass* r);
    void setPredeterminedVerdict(bool pv);
protected:

    //data members
    bool _PredeterminedPassType;
    bool _PredeterminedVerdict; // false is dead
    bool _PassType;
    int _ScytheUse; //for unwilling passengers only 


private:
    Node* _currentNode;
    Ticket* _Ticket;
    RailPass* _RailPass;
};

