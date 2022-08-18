#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>
#include <SDL.h>

class Player {
	SDL_Point _coords;
	std::string ruleBook[2];
	int ruleBookDay;
	bool ruleBookPassType;
public: 
	Player();
	~Player();
	SDL_Point getCoords();
	bool compareToBook(InteractablePerson p, int attribute);
	bool giveVerdict(std::string chosenVerdict);
	void playerMovement();
	bool getPassType();
};
	