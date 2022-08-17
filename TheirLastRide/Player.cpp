#include "Player.h"

Player::Player() {

}
Player::~Player() {

}

SDL_Point Player::getCoords()
{
	return _coords;
}


bool Player::compareToBook(Ticket* ticket)
{
	return false;
}

bool Player::checkTicket(InteractablePerson passenger)
{
		compareToBook(passenger.getTicket());
	
}

bool Player::giveVerdict(std::string chosenVerdict)
{
	bool verdict;
	verdict = (chosenVerdict == "alive") ? true : false;
	return verdict;
}

void Player::playerMovement()
{
	char movementKeys;

	switch (movementKeys)
	{
	case 'W':
		_coords.y--;
		break;
	case 'A':
		_coords.x--;
		break;
	case 'S':
		_coords.x++;
		break;
	case 'D':
		_coords.y++;
		break;
	}
}


