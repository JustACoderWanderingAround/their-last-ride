#pragma once
class Passenger
{
public:

	//functions
	int getPixelX();
	int getPixelY();
	int getName();


protected:

	//data members
	virtual void interact(Passenger p) = 0;
	int _PixelX;
	int _PixelY;
	int _Name;

};

