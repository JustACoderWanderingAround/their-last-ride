#pragma once
#include <vector>
#include <string>
class Ticket
{
public:
	Ticket();
	Ticket(std::string iS, std::vector<std::string> dS, int iD);
	~Ticket();
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

