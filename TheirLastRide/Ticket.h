#pragma once
#include <string>
class Ticket
{
public:
	std::string getIssuingStn();
	std::string getDestination();
	std::string getIssueDate();

private:
	std::string _IssuingStn;
	std::string _Destination;
	std::string _IssueDate;
};

