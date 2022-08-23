#include "Player.h"

Player::Player() {
	ruleBook[0] = "Noston Central";
	ruleBook[1] = "Noston Central";
	_ruleBookDay = 0;
	_coords = { 700, 300 };
}

Player::Player(std::vector<std::string> stops){
	ruleBook[0] = "Noston Central";
	for (auto stop : stops) {
		ruleBook[0] += ", ";
		ruleBook[0] += stop;
	}
	
	ruleBook[1] = "Noston Central";
	_ruleBookDay = 0;
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
	Ticket* ticket = p.getTicket();
	RailPass* railpass = p.getRailPass();
	switch (attribute) {
	case 1:
		return (ruleBook[0].find(ticket->getDestination()));
	case 2:
		return (getDay() == ticket->getIssueDate());
	case 3:
		return (ruleBook[1] == ticket->getIssuingStn());
	case 4:
		return (railpass->getName() == p.getName());
	case 5: 
		return (railpass->getPassType() == p.getPassType());
	case 6: 
		return (railpass->getExpiry() >= getDay());
	default:
		return false;
	}
}

bool Player::giveVerdict(std::string chosenVerdict)
{
	return (chosenVerdict == "alive");
}

void Player::playerMovement()
{

}

bool Player::getPassType()
{
	return _ruleBookPassType;
}

int Player::getDay()
{
	return _ruleBookDay;
}

void Player::setDay(int day)
{
	_ruleBookDay = day;
}


