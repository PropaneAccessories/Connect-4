#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL.h"
#include <string>

using namespace std;

class Texture
{
public:
    Texture();
    void loadMedia(string path, SDL_Renderer* gRenderer);
    void animatePiece();
    void renderImage(SDL_Renderer *gRenderer);
    void render(SDL_Renderer *gRenderer);
    void createStringTexture(string str, SDL_Renderer *gRenderer, int sz);
    void free();

    /*** Setters ***/
    void setPieceDestination(int Pos);
    void setDestRect(int x, int y, int width, int height);
    void setInPos();
    void setImage();
    void setShow(bool b);

    /*** Getters **/
    bool isInPos();
    bool isImage();
    bool shouldShow();

private:
    SDL_Texture *texture;
    SDL_Rect destRect;
    int YPos;
    int XPos;
    float velocity;
    float velocityPrevious;
    bool image;
    bool inPos;
    bool show;
};

#endif // TEXTURE_H
