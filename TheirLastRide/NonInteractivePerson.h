#pragma once
#include "Person.h"
class Person;
class Scene;
class NonInteractivePerson :
    public Person
{
private:
    int _NonInteractiveReply;
    void interact();
};