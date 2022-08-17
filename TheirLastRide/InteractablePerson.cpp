#include "InteractablePerson.h"
#include <iostream>

void InteractablePerson::interact()
{
	//interaction 
}

bool InteractablePerson::verdictChecker(bool _PlayerVerdict)
{
	
	return (_PlayerVerdict == _PredetermindedVerdict);
	
}
Ticket InteractablePerson::getTicket()
{
	return _Ticket;
}

