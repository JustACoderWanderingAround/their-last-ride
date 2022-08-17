#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include "Ticket.h"
#include <string>

class Player {
	int x;
	int y;
	std::string rulebook[5];
public: 
	Player();
	~Player();
	int getX();
	int getY();
	void openBook();
	void checkTicket(InteractablePerson passenger);
	void compareToBook(Ticket* ticket);
	void interact(Person p);
};
	