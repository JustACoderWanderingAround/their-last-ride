#include "TextManager.h"

TextManager::TextManager()
{
	_fonts[FONT_RENDESEK] = TTF_OpenFont("Fonts//REDENSEK.TTF", 24);
}

void TextManager::RenderText(const std::string& message)
{

}
