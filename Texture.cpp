#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <cmath>

Texture::Texture()
{
    texture = NULL;
    destRect = {0,0,0,0};
    YPos = 0;
    XPos = 0;
    velocity = -100.0;
    velocityPrevious = 0.0;
    inPos = false;
    image = false;
    show = true;
}

void Texture::loadMedia(string path, SDL_Renderer *gRenderer)
{
    SDL_Surface *s = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(gRenderer, s);
    SDL_FreeSurface(s);
}

void Texture::animatePiece()
{
    // speed governor too keep the animation from appearing too fast
    if(velocity < 50)
    {
        velocity += (velocityPrevious + 0.25);
        velocityPrevious = abs(velocity/2);
    }
    else velocity += 25;

    if(velocity < YPos)
        destRect = {XPos, velocity, 100,100};
    else
    {
        destRect = {XPos, YPos, 100,100};
        inPos = true;
    }
}

void Texture::renderImage(SDL_Renderer *gRenderer)
{
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);
}

void Texture::render(SDL_Renderer *gRenderer)
{
    SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
}

void Texture::createStringTexture(string str, SDL_Renderer *gRenderer, int sz)
{
    SDL_Color black;
        black.r = 0;
        black.g = 0;
        black.b = 0;
        black.a = 0;
    TTF_Font *ttfText = TTF_OpenFont("veraFonts/VeraSe.ttf", sz);
    SDL_Surface *s1 = TTF_RenderText_Blended(ttfText, str.c_str(), black);
    texture = SDL_CreateTextureFromSurface(gRenderer, s1);
    SDL_FreeSurface(s1);
}

void Texture::free() {SDL_DestroyTexture(texture);}


/*** Setters ***/

void Texture::setPieceDestination(int pos)
{
    XPos = (pos%7) * 100;
    YPos = (pos/7) * 100;
}

void Texture::setDestRect(int x, int y, int width, int height) {destRect = {x,y,width,height};}

void Texture::setInPos() {inPos = true;}

void Texture::setImage()
{
    image = true;
    inPos = true;
}

void Texture::setShow(bool b) {show = b;}


/*** Getters ***/

bool Texture::isInPos() {return inPos;}

bool Texture::isImage() {return image;}

bool Texture::shouldShow() {return show;}


