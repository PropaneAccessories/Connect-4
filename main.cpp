/**
To Do List

- Build a home screen
- delay the win/lose screen for  the piece animation to complete. Maybe make a highlight function that highlights the pieces
- fix the animation bug where the pieces drop fast, then slow, then accelerate.
- Make an actual AI
- Menu options on home screen and end of game screen.
- Don't allow player to make move while animation is running

**/


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Texture.h"
#include "GameArray.h"
#include "AI.h"
#include <string>
#include <vector>

using namespace std;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
GameArray gGameBoard;
string EndingMessage[3] = {"You Won!", "You Lost!", "Draw!"};
vector<Texture> graphics;
vector<Texture> images;

enum GameState {NotOver = 0, Player1Win, AIWin, Draw};

bool playerMoves(Texture &t, const int mouseX);
void render();
void renderGraphicsVector();
bool isDoneAnimating();
void createEndScreen(int condition);
void initialize();
void checkHighlights();
void close();

int main(int argc, char *argv[])
{
    bool quit = false;
    bool moved = false;
    bool endflag = true;
    bool playAgain = false;
    int gameOver = 0;
    int mouseX = 0;
    int mouseY = 0;

    /*** Initialize The Game ***/
    initialize();
    SDL_Event e;

    /*** GAME LOOP ***/
    while(!quit)
    {
        /***
        Welcome screen. Choose difficulty level, then play or quit
        Hold player here until they decide
        while(home)
        {
            // render home screen and such
        }
        ***/
        checkHighlights();

        /*** The Event Loop. Handles player input during game ***/
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_MOUSEBUTTONUP && !moved)
            {
                SDL_GetMouseState(&mouseX, NULL);
                Texture t;
                moved = playerMoves(t, mouseX);
                if(moved)
                {
                    t.loadMedia("Graphics/red.png", gRenderer);
                    graphics.push_back(t);
                }
                else t.free();
            }
        }
        while(!isDoneAnimating()) {render();}
        render();
        gameOver = gGameBoard.checkGameOver();

        /*** If the player made a move, have the AI go ***/
        if(moved && gameOver == 0)
        {
            SDL_Delay(100);
            Texture AI;
            AI.loadMedia("Graphics/black.png", gRenderer);
            AI.setPieceDestination(gGameBoard.getPositionPlayer2(AImoveEasy(gGameBoard)));
            graphics.push_back(AI);
            moved = false;
        }
        render();
        gameOver = gGameBoard.checkGameOver();

        /*** End of Game Loop ***/
        while(gameOver != 0)
        {
            if(endflag)
            {
                createEndScreen(gameOver);
                endflag = false;
            }

            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                    gameOver = false;
                }
            }
            //SDL_GetMouseState(&mouseX, &mouseY);

            render();
        }
    }

    close();
    return 0;
}

void render()
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    renderGraphicsVector();
    SDL_RenderPresent(gRenderer);
}

void renderGraphicsVector()
{
    vector<Texture>::iterator iter1 = graphics.begin();
    vector<Texture>::iterator iter2 = images.begin();
    for(iter1; iter1 != graphics.end(); iter1++)
    {
        iter1->render(gRenderer);
        if(!iter1->isInPos())
        {
            iter1->animatePiece();
        }
    }

    for(iter2; iter2 != images.end(); iter2++)
    {
        if(iter2->isImage())
            iter2->renderImage(gRenderer);
        else if(iter2->shouldShow())
            iter2->render(gRenderer);
    }
}

void createEndScreen(int condition)
{
    Texture endScreen;
    endScreen.loadMedia("Graphics/endScreen.png", gRenderer);
    endScreen.setDestRect(150,50,400,250);

    Texture endMessage;
    switch (condition)
    {
    case Player1Win:
        endMessage.createStringTexture(EndingMessage[0], gRenderer, 50);
        break;
    case AIWin:
        endMessage.createStringTexture(EndingMessage[1], gRenderer, 50);
        break;
    case Draw:
        endMessage.createStringTexture(EndingMessage[2], gRenderer, 50);
        break;
    }
    endMessage.setDestRect(275,100, 150,50);

    Texture playAgain;
    playAgain.createStringTexture("Play Again?", gRenderer, 40);
    playAgain.setDestRect(210,230,100,30);
    Texture quit;
    quit.createStringTexture("Quit", gRenderer, 40);
    quit.setDestRect(410,230,50,30);

    images.push_back(endScreen);
    images.push_back(endMessage);
    images.push_back(playAgain);
    images.push_back(quit);
}

void initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    gWindow = SDL_CreateWindow("Connect 4",
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        700,600, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface *s1 = IMG_Load("Graphics/icon.png");
    SDL_SetWindowIcon(gWindow, s1);
    SDL_FreeSurface(s1);

    Texture backHighlight;
    backHighlight.loadMedia("Graphics/BoardHighlight.png", gRenderer);
    backHighlight.setDestRect(0,0,100,600);
    backHighlight.setInPos();

    Texture background;
    background.loadMedia("Graphics/BoardYellow.png", gRenderer);
    background.setImage();
    background.setInPos();

    graphics.push_back(backHighlight);
    images.push_back(background);
}

void checkHighlights()
{
    int x = 0;
    SDL_GetMouseState(&x, NULL);
    if(x >= 0 && x < 100)
    {
        graphics[0].setDestRect(0,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 100 && x < 200)
    {
        graphics[0].setDestRect(100,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 200 && x < 300)
    {
        graphics[0].setDestRect(200,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 300 && x < 400)
    {
        graphics[0].setDestRect(300,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 400 && x < 500)
    {
        graphics[0].setDestRect(400,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 500 && x < 600)
    {
        graphics[0].setDestRect(500,0,100,600);
        graphics[0].setShow(true);
    }
    if(x >= 600 && x < 700)
    {
        graphics[0].setDestRect(600,0,100,600);
        graphics[0].setShow(true);
    }
}

bool isDoneAnimating()
{
    vector<Texture>::iterator iter = graphics.begin();
    for(iter; iter != graphics.end(); iter++)
    {
        if(!iter->isInPos())
            return false;
    }
    return true;
}

bool playerMoves(Texture &t, const int mouseX)
{
    if(mouseX > 0 && mouseX < 100){
        if(!gGameBoard.isColumnFull(0)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(0));
            return true;
        }
    }
    if(mouseX > 100 && mouseX < 200){
        if(!gGameBoard.isColumnFull(1)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(1));
            return true;
        }
    }
    if(mouseX > 200 && mouseX < 300){
        if(!gGameBoard.isColumnFull(2)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(2));
            return true;
        }
    }
    if(mouseX > 300 && mouseX < 400){
        if(!gGameBoard.isColumnFull(3)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(3));
            return true;
        }
    }
    if(mouseX > 400 && mouseX < 500){
        if(!gGameBoard.isColumnFull(4)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(4));
            return true;
        }
    }
    if(mouseX > 500 && mouseX < 600){
        if(!gGameBoard.isColumnFull(5)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(5));
            return true;
        }
    }
    if(mouseX > 600 && mouseX < 700){
        if(!gGameBoard.isColumnFull(6)){
            t.setPieceDestination(gGameBoard.getPositionPlayer1(6));
            return true;
        }
    }
    return false;
}

void close()
{
    vector<Texture>::iterator iter = graphics.begin();
    for(iter; iter != graphics.end(); iter++)
    {
        iter->free();
    }
    vector<Texture>::iterator iter2 = images.begin();
    for(iter2; iter2 != images.end(); iter2++)
    {
        iter2->free();
    }
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


/*
0   1   2   3   4   5   6
7   8   9   10  11  12  13
14  15  16  17  18  19  20
21  22  23  24  25  26  27
28  29  30  31  32  33  34
35  36  37  38  39  40  41
*/

