#pragma once
#include <string>
class Ticket
{
public:
	std::string getIssuingStn();
	std::string getDestination();
	int getIssueDate();
	bool getClippedState();
	void setClippedState(bool state);
private:
	std::string _IssuingStn;
	std::string _Destination;
	bool _clipped;
	int _IssueDate;
};

