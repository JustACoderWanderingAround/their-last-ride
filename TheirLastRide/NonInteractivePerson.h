#pragma once
#include "Person.h"
class NonInteractivePerson :
    public Person
{
private:
    int _NonInteractiveReply;
    void interact();
};