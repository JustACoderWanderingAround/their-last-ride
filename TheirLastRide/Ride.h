#pragma once
#include <string>
#include <vector>
class Ride
{
	int _interactableNumber;
	int _nonInteractableNumber;
	int _carriageNum;
	int _date;
	int _wrongVerdictCount;
	int _numAlive;
	int _numDead;
	std::string _start;
	std::vector<std::string> _stops;
	std::vector<std::string> _invalidStops;
	std::vector<std::string> _interactablePeople;
public:
	/*std::string start;
	std::vector<std::string> stops;
	std::vector<std::string> invalidStops;
	std::vector<std::string> interactablePeople;*/
	Ride();
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN);
	Ride(std::string str, std::vector<std::string> stp, int iN, int nN, int cN, int d);
	~Ride();
	int getInteractable();
	int getNonInteractable() const;
	int getCarriageNum() const;
	int getDate() const;
	int getWrongVerdict();
	void setNumAlive(int nA);
	void setNumDead(int nD);
	int getNumAlive();
	int getNumDead();
	/*bool loadAttributes(int rideNumber);*/
	void setStart(const std::string& s);
	void setStops(const std::vector<std::string>& s);
	void setInvalidStops(const std::vector<std::string>& is);
	void setInteractablePeople(const std::vector<std::string>& ip);
	std::string getStart() const;
	std::vector<std::string> getStops() const;
	std::vector<std::string> getInvalidStops() const;
	std::vector<std::string> getInteractablePeople() const;
	void setDate(int d);
	void setInteractableNumber(int in);
	void setNonInteractableNumber(int nin);
	void setCarriageNum(int cn);
	void setWrongVerdict(int wv);
	bool operator==(const std::string& s) const;
	bool checkInteractable(const std::string& name);
};

