#pragma once
#include "Person.h"
class NonInteractivePerson :
    public Person
{
    void interact(Player p);


private:
    int _NonInteractiveReply;
};