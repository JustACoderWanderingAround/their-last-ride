#pragma once
#include <string>
#include <vector>

class Ticket
{
public:
	Ticket();
	Ticket(std::vector<std::string> dS, std::vector<std::string> randStops, int iD);
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

