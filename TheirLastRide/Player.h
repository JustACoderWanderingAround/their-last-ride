#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>
#include <SDL.h>

class Player {
	SDL_Point _coords;
	std::string ruleBook[5];
public: 
	Player();
	~Player();
	SDL_Point getCoords();
	bool checkTicket(InteractablePerson passenger);
	bool compareToBook(Ticket* ticket);
	bool giveVerdict(std::string chosenVerdict);
};
	