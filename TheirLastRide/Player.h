#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>

class Player {
	int x;
	int y;
	std::string ruleBook[5];
public: 
	Player();
	~Player();
	int getX();
	int getY();
	bool checkTicket(InteractablePerson passenger);
	bool compareToBook(Ticket* ticket);
	bool giveVerdict(std::string chosenVerdict);
	void playerMovement();
};
	