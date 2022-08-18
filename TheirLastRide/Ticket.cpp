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
