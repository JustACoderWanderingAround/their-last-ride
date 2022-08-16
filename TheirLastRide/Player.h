#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>

class Player {
	int x;
	int y;
	std::string rulebook;
public: 
	Player();
	~Player();
	int getX();
	int getY();
	void openBook();
	void checkTicket(InteractablePerson passenger);
	void compareToBook(Ticket* ticket);
	void talkToPassenger(InteractablePerson passenger);
	void talkToPassenger(NonInteractivePerson passenger);
};
	