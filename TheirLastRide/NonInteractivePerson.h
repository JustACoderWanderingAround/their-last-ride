#pragma once
#include "Person.h"
class Person;
class Scene;
class NonInteractivePerson :
    public Person
{
private:
    std::string _msg;
public:
    NonInteractivePerson();
    std::string getMessage() const;
    void setMessage(const std::string& m);
};