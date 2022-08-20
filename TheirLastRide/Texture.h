#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "TextManager.h"
#include "Text.h"

/// <summary>
/// SDL_Texture wrapper class.
/// </summary>
class Texture
{
private:
	SDL_Texture* _texture;
	void* _pixels;
	int _pitch;
	int _width;
	int _height;
public:
	Texture();
	~Texture();
	bool operator!();
	bool loadImage(std::string path);
	bool loadText(const Text& text);
	bool loadText(const std::string& message, TTF_Font* font, SDL_Color textcolor);
	bool createBlank(int width, int height, SDL_TextureAccess access = SDL_TEXTUREACCESS_STREAMING);
	void setColor(unsigned int r, unsigned int g, unsigned int b);
	void setAlpha(unsigned int a);
	void setBlendMode(SDL_BlendMode bm);
	void setScale(float x, float y);
	void setScale(float scalar);
	void free();
	void Render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* centre = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void* getPixels();
	int getWidth();
	int getHeight();
	int getPitch();
	void setWidth(int w);
	void setHeight(int h);

	bool lockTexture();
	bool unlockTexture();
};

