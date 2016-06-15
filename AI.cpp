#include "AI.h"
#include "GameArray.h"
#include "Texture.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int AImoveEasy(GameArray &g)
{
    int random = 0;
    do
    {
        srand(time(NULL));
        random = rand() % 7;
    } while(g.isColumnFull(random));     // returns true if column is full

    return random;
}
