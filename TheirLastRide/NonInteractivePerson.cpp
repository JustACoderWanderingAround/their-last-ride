#include "NonInteractivePerson.h"
#include "Player.h"
#include "ObjectBuilder.h"
#include "Application.h"
#include <iostream>

NonInteractivePerson::NonInteractivePerson()
{
	std::vector<std::string> spriteLst = { "Richward", "Maisie" , "Jeanie" };
	int nameIndex = rand() % spriteLst.size();
	Texture selfTexture;
	selfTexture.loadImage("Sprites//Passengers//" + spriteLst[nameIndex] + ".PNG");
	selfTexture.setBlendMode(SDL_BLENDMODE_BLEND);
	selfTexture.setScale(1.1);
	_txt = selfTexture;
}

std::string NonInteractivePerson::getMessage() const
{
	return _msg;
}

void NonInteractivePerson::setMessage(const std::string& m)
{
	_msg = m;
}
