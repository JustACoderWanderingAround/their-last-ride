#include "TrainCabin.h"
#include <vector>
#include <iostream>

/// <summary>
/// Initialize the cabin.
/// </summary>
TrainCabin::TrainCabin()
{
	srand(time(0));
	_seats.fill(nullptr);
	fillSeats();
}

TrainCabin::~TrainCabin()
{
	/*for (auto seat : _seats) {
		if (seat != nullptr) {
			delete seat;
		}
	}*/
}

/// <summary>
/// Fill the seats randomly.
/// </summary>
void TrainCabin::fillSeats()
{
	std::vector<std::string> names = { "George", "Sasha" }; // to be changed
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
		_seats[positions[rand() % no_of_positions]] = new InteractablePerson(names[rand() % 2]);
	}
	/*for (int i = 0; i < no_of_positions; i++)
	{
		_seats[positions[i]] = new InteractablePerson(names[rand() % 2]);
	}*/
	_seats[0] = new InteractablePerson(names[0]);
}

std::array<Person*, number_of_seats> TrainCabin::getSeats()
{
	return _seats;
}

/// <summary>
/// Convert the position on the 4x6 array to an SDL_Point (intvector2)
/// </summary>
/// <param name="position">Position on the array</param>
/// <returns>(x, y)</returns>
SDL_Point TrainCabin::ConvertToPoint(const int& position)
{
	return { position % 4, (position - (position % 4)) / 6 };
}

/// <summary>
/// Convert an SDL_Point (intvector2) to a position on the 4x6 array.
/// </summary>
/// <param name="vec">The IntVector2</param>
/// <returns>Position on the array</returns>
int TrainCabin::ConvertToPosition(const SDL_Point& vec)
{
	return (vec.x +( vec.y * 4));
}


