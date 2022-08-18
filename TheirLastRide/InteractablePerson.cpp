#include "InteractablePerson.h"
#include "Player.h"
#include <iostream>


void InteractablePerson::interact(Player p)
{
	std::cout << "temp" << std::endl;
}

bool InteractablePerson::verdictChecker(bool _PlayerVerdict)
{
	
	return (_PlayerVerdict == _PredetermindedVerdict);
	
}
Ticket InteractablePerson::getTicket()
{
	return _Ticket;
}
RailPass InteractablePerson::getRailPass()
{
	return _RailPass;
}

