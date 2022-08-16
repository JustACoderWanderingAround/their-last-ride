#include "TrainCabin.h"
#include <vector>
#include <iostream>

TrainCabin::TrainCabin()
{
	srand(time(0));
	_seats.fill(nullptr);
	fillSeats();
}

TrainCabin::~TrainCabin()
{
	for (auto seat : _seats) {
		if (seat != nullptr) {
			delete seat;
		}
	}
}

void TrainCabin::fillSeats()
{
	unsigned short amountOfNonInteractablePeople = rand() % 5 + 1;
	unsigned short amountOfInteractablePeople = 5; // to be changed according to level.
	std::vector<int> positions;
	for (int i = 0; i < number_of_seats; i++)
	{
		if (ConvertToPoint(i).x == 0 || ConvertToPoint(i).x == 3)
			positions.push_back(i);
	}
	size_t no_of_positions = positions.size();
	for (int i = 0; i < amountOfNonInteractablePeople; i++)
	{
		_seats[positions[rand() % no_of_positions]] = new NonInteractivePerson();
	}
	positions.clear();
	for (int i = 0; i < number_of_seats; i++)
	{
		if (ConvertToPoint(i).x == 1 || ConvertToPoint(i).x == 2)
			positions.push_back(i);
	}
	no_of_positions = positions.size();
	for (int i = 0; i < amountOfInteractablePeople; i++)
	{
		_seats[positions[rand() % no_of_positions]] = new InteractablePerson();
	}
	/*for (int i = 0; i < number_of_seats; i++)
	{
		std::cout << _seats[i] << std::endl;
	}*/
}

std::array<Person*, number_of_seats> TrainCabin::getSeats()
{
	return _seats;
}

SDL_Point TrainCabin::ConvertToPoint(const int& position)
{
	return { position % 4, (position - (position % 4)) / 6 };
}

int TrainCabin::ConvertToPosition(const SDL_Point& vec)
{
	return (vec.x +( vec.y * 6));
}


