#include "Ride.h"

Ride::Ride()
{
}

Ride::Ride(std::string str, std::vector<std::string> stp, int iN, int nN)
{
    _start = str;
    _stops = stp;
    _interactableNumber = iN;
    _nonInteractableNumber = nN;
}

Ride::~Ride()
{
}

std::string Ride::getStart()
{
    return _start;
}

std::vector<std::string> Ride::getStops()
{
    return _stops;
}

int Ride::getInteractable()
{
    return _interactableNumber;
}

int Ride::getNonInteractable()
{
    return _nonInteractableNumber;
}
