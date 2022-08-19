#include "Ticket.h"

Ticket::Ticket()
{
    _IssuingStn = "Noston Central";
    _Destination = "Noston East";
    _IssueDate = 1;
}

Ticket::Ticket(std::string iS, std::string dS, int iD)
{
    _IssuingStn = iS;
    _Destination = dS;
    _IssueDate = iD;
}

Ticket::~Ticket()
{
}

std::string Ticket::getIssuingStn()
{
    return _IssuingStn;
}

std::string Ticket::getDestination()
{
    return _Destination;
}

int Ticket::getIssueDate()
{
    return _IssueDate;
}

bool Ticket::getClippedState()
{
    return _clipped;
}

void Ticket::setClippedState(bool state)
{
    _clipped = state;
}

