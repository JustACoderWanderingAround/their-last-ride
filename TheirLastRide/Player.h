#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>
#include <SDL.h>
class Player { 
	SDL_Point _coords;
	std::string ruleBook[2];
	int _ruleBookDay;
	bool _ruleBookPassType;
public: 
	Player();
	Player(std::vector<std::string> stops);
	~Player();
	SDL_Point getCoords();
	bool compareToBook(InteractablePerson* p, int attribute);
	bool giveVerdict(std::string chosenVerdict);
	void playerMovement();
	bool getPassType();
	int getDay();
	void setDay(int day);
};
	