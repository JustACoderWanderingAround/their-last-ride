#include "Application.h"
#include "Player.h"
#include "Ticket.h"
#include "RailPass.h"
#include "InteractablePerson.h"
#include "Ride.h"
#include <iostream>

int main(void)
{
	//Application* app = Application::GetInstance();
	//app ->Init();
	//app ->Run();
	//app ->Exit();
	Ride* ride1 = new Ride;
	std::cout << ride1->start;
	return 0;
}