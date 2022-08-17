#include "NonInteractivePerson.h"
#include "Player.h"
#include <iostream>

void NonInteractivePerson::interact(Player p)
{
	std::cout << _NonInteractiveReply << std::endl;
}

