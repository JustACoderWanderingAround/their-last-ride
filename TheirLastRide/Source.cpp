#include "Application.h"
#include "Player.h"
#include "Ticket.h"
#include "RailPass.h"
#include "InteractablePerson.h"
#include "Ride.h"
#include <iostream>

int main(void)
{
	Application* app = Application::GetInstance();
	app ->Init();
	app ->Run();
	app ->Exit();
	/*Ticket* ticket1 = new Ticket("Stop A", "Stop B", 1);
	RailPass* railpass1 = new RailPass("name", false, 1);
	Player* playerOne = new Player({ "Stop A", "Stop B" });

	InteractablePerson* pass1 = new InteractablePerson("name", false, false, ticket1, railpass1);

	std::cout << playerOne->compareToBook(*pass1, 1) << std::endl;
	std::cout << playerOne->compareToBook(*pass1, 2) << std::endl;
	std::cout << playerOne->compareToBook(*pass1, 3) << std::endl;
	std::cout << playerOne->compareToBook(*pass1, 4) << std::endl;
	std::cout << playerOne->compareToBook(*pass1, 5) << std::endl;
	std::cout << playerOne->compareToBook(*pass1, 6) << std::endl;*/
	Ride* ride1 = new Ride();
	ride1->loadAttributes(2);
	std::cout << ride1->start;
	std::cout << ride1->stops[0];
	std::cout << ride1->stops[1];
	std::cout << ride1->stops[2];
	return 0;
}