#include "Ticket.h"

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

