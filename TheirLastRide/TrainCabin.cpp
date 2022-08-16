#include "TrainCabin.h"

TrainCabin::TrainCabin()
{
	_seats.fill(nullptr);
}

TrainCabin::~TrainCabin()
{
	for (auto seat : _seats) {
		if (seat != nullptr) {
			delete seat;
		}
	}
}
