#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
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
	bool loadImage(std::string path);
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

	bool lockTexture();
	bool unlockTexture();
};

