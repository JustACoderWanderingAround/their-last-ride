#pragma once
#include <array>
#include "Person.h"
#include "InteractablePerson.h"
#include "NonInteractivePerson.h"
#include <SDL.h>

constexpr unsigned int number_of_seats = 24;
class TrainCabin
{
private:
	std::array<Person*, number_of_seats> _seats;
public:
	TrainCabin();
	~TrainCabin();
	void fillSeats();
	static SDL_Point ConvertToPoint(const int& position);
	static int ConvertToPosition(const SDL_Point& vec);
};

