#include "InteractablePerson.h"
#include <iostream>


void InteractablePerson::interact()
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

