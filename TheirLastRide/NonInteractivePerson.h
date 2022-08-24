#pragma once
#include "Person.h"
class Person;
class Scene;
class NonInteractivePerson :
    public Person
{
private:
    std::string msg;
public:
    NonInteractivePerson();
    std::string getMessage() const;
};