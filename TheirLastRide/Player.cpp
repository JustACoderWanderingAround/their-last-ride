#include "Player.h"


Player::Player() {
	this->x = 0;
	this->y = 0;
}
Player::~Player() {

}
int Player::getX()
{
	return this->x;
}

int Player::getY()
{
	return this->y;
}

void Player::openBook()
{
}

void Player::checkTicket(InteractablePerson passenger)
{
}

void Player::compareToBook(Ticket* ticket)
{

}

void Player::talkToPassenger(InteractablePerson passenger)
{
}

void Player::talkToPassenger(NonInteractivePerson passenger)
{
}

