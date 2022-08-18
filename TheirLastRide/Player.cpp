#include "Player.h"

Player::Player() {
	ruleBook[0] = "Noston Central, Noston East, Ewing Bridge";
	ruleBook[1] = "Noston Central";
	ruleBookDay = 0;
	_coords = { 700, 300 };
}
Player::~Player() {

}

SDL_Point Player::getCoords()
{
	return _coords;
}


bool Player::compareToBook(InteractablePerson p, int attribute)
{
	Ticket ticket = p.getTicket();
	RailPass railpass = p.getRailPass();
	switch (attribute) {
	case 1:
		return (ruleBook[0].find(ticket.getDestination()));
	case 2:
		return (ruleBookDay == ticket.getIssueDate());
	case 3:
		return (ruleBook[2] == ticket.getIssuingStn());
	case 4:
		return (railpass.getName() == p.getName());
	case 5: 
		return (railpass.getPassType() == p.getPassType());
	case 6: 
		return (railpass.getExpiry() <= ruleBookDay);
	}
}

bool Player::giveVerdict(std::string chosenVerdict)
{
	bool verdict;
	verdict = (chosenVerdict == "alive") ? true : false;
	return verdict;
}

void Player::playerMovement()
{
	char movementKeys = 'A';

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

std::string Player::getPassType()
{
	return passType;
}


