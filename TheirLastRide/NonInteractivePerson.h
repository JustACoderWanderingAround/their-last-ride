#pragma once
#include "Person.h"
class NonInteractivePerson :
    public Person
{
    void interact();


private:
    int _NonInteractiveReply;
};