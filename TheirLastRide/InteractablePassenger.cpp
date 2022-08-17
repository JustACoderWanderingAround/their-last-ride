#include "InteractablePassenger.h"
#include <iostream>

void InteractablePassenger::interact()
{
	//interaction 
}

bool InteractablePassenger::verdictChecker(bool _PlayerVerdict)
{
	
	return (_PlayerVerdict == _PredetermindedVerdict);
	
}
Ticket InteractablePassenger::getTicket()
{
	return _Ticket;
}

