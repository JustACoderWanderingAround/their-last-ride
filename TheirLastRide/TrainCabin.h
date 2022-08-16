#pragma once
#include <array>
#include "Person.h"
constexpr unsigned int number_of_seats = 12;
class TrainCabin
{
private:
	std::array<Person*, number_of_seats> _seats;
public:
	TrainCabin();
	~TrainCabin();
};

