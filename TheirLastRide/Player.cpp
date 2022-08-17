#include "Player.h"


Player::Player() {
	this->x = 0;
	this->y = 0;
}
Player::~Player() {

}
int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

bool Player::compareToBook(Ticket* ticket)
{
	return false;
}

bool Player::checkTicket(InteractablePerson passenger)
{
	for (int ticketAttribute = 0; ticketAttribute < 3; ticketAttribute++) {
		compareToBook(passenger.getTicket());
	}
}



bool Player::giveVerdict(std::string chosenVerdict)
{
	bool verdict;
	verdict = (chosenVerdict == "alive") ? true : false;
	return verdict;
}


