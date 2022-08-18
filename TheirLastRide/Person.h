#pragma once
class Player;
class Person
{
public:
	virtual void interact(Player p) = 0;
	int getPersonName();

protected:
	int _PersonName;
};



