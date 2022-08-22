#include "Ticket.h"

Ticket::Ticket()
{
    _IssuingStn = "NOSTON CTRL";
    _Destination = "NOSTON EAST";
    _IssueDate = 1;
}

Ticket::Ticket(std::vector<std::string> dS, std::vector<std::string> randStops, int iD)
{
    int i = rand() % dS.size();
    int j = rand() % 10;
    
    _IssuingStn = "NOSTON CTRL";
    _Destination = dS[i];
    _IssueDate = iD;

    switch (j)
    {
    case 0:
        int k = rand() % dS.size();
        _IssuingStn = dS[k];
        break;
    
    case 1:
        int l = rand() % randStops.size();
        _Destination = randStops[k];
        break;

    case 2:
        _IssueDate = rand() % 31 + 1;
        break;

    }
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

