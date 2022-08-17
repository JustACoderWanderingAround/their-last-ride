#pragma once

class Person
{
public:

	//functions
	int getPixelX();
	int getPixelY();
	int getName();


protected:

	//data members
	virtual void interact() = 0;
	int _PixelX;
	int _PixelY;
	int _Name;

};

