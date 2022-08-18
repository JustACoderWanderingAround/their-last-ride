#pragma once
#include <string>
class Ticket
{
public:
	std::string getIssuingStn();
	std::string getDestination();
	int getIssueDate();

private:
	std::string _IssuingStn;
	std::string _Destination;
	int _IssueDate;
};

