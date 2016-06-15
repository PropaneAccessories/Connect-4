#include "GameArray.h"

using namespace std;

enum OCCUPIED {OPEN = 0, PLAYER1, AI};

GameArray::GameArray()
{
    for(int i=0; i<42; i++)
    {
        board[i] = OPEN;
    }
}

bool GameArray::isColumnFull(int column)
{
    switch(column)
    {
    case 0:
        if(board[0] != 0 && board[7] != 0 && board[14] != 0 && board[21] != 0 && board[28] != 0 && board[35] != 0)
            return true;
        break;
    case 1:
        if(board[1] != 0 && board[8] != 0 && board[15] != 0 && board[22] != 0 && board[29] != 0 && board[36] != 0)
            return true;
        break;
    case 2:
        if(board[2] != 0 && board[9] != 0 && board[16] != 0 && board[23] != 0 && board[30] != 0 && board[37] != 0)
            return true;
        break;
    case 3:
        if(board[3] != 0 && board[10] != 0 && board[17] != 0 && board[24] != 0 && board[31] != 0 && board[38] != 0)
            return true;
        break;
    case 4:
        if(board[4] != 0 && board[11] != 0 && board[18] != 0 && board[25] != 0 && board[32] != 0 && board[39] != 0)
            return true;
        break;
    case 5:
        if(board[5] != 0 && board[12] != 0 && board[19] != 0 && board[26] != 0 && board[33] != 0 && board[40] != 0)
            return true;
        break;
    case 6:
        if(board[6] != 0 && board[13] != 0 && board[20] != 0 && board[27] != 0 && board[34] != 0 && board[41] != 0)
            return true;
        break;
    default:
        return false;
    }
    return false;
}

int GameArray::getPositionPlayer1(int column)
{
    int pos = -1;
    for(column; column <= 41; column += 7)
    {
        if(board[column] == 0)
        {
            pos = column;
        }
        else break;
    }
    board[pos] = PLAYER1;
    return pos;
}

int GameArray::getPositionPlayer2(int column)
{
    int pos = -1;
    for(column; column <= 41; column += 7)
    {
        if(board[column] == 0)
        {
            pos = column;
        }
        else break;
    }
    board[pos] = AI;
    return pos;
}

int GameArray::getArrayVal(int pos)
{
    return board[pos];
}

int GameArray::checkGameOver()
{
    // Check if Game is a draw/board is full
    for(int i=0; i<42; i++)
    {
        if(board[i] == 0)
            break;
        else
            return 3;
    }

    // check player1
    for(int i=0; i<42; i++)
    {
        if(board[i] == PLAYER1)
        {
            // test if the player won by vertically
            if(i <= 20)
            {
                if(board[i+7] == PLAYER1 && board[i+14] == PLAYER1 && board[i+21] == PLAYER1)
                    return 1;
            }
            // test if player won horizontally
            if(i%7 <= 3)
            {
                if(board[i+1] == PLAYER1 && board[i+2] == PLAYER1 && board[i+3] == PLAYER1)
                    return 1;
            }
            // check if player won on a right diagonal
            if(i<=3 || (i >= 7 && i <= 10) || (i >= 14 && i <= 17) )
            {
                if(board[i+8] == PLAYER1 && board[i+16] == PLAYER1 && board[i+24] == PLAYER1)
                    return 1;
            }
            // check if player won on a left diagonal
            if( (i >= 3 && i <= 6) || (i >= 10 && i <= 13) || (i >= 17 && i <= 20) )
            {
                if(board[i+6] == PLAYER1 && board[i+12] == PLAYER1 && board[i+18] == PLAYER1)
                    return 1;
            }
        }
    }

    // check AI
    for(int i=0; i<42; i++)
    {
        if(board[i] == AI)
        {
            // test if the AI won by vertically
            if(i <= 20)
            {
                if(board[i+7] == AI && board[i+14] == AI && board[i+21] == AI)
                    return 2;
            }
            // test if AI won horizontally
            if(i%7 <= 3)
            {
                if(board[i+1] == AI && board[i+2] == AI && board[i+3] == AI)
                    return 2;
            }
            // check if AI won on a right diagonal
            if(i<=3 || (i >= 7 && i <= 10) || (i >= 14 && i <= 17) )
            {
                if(board[i+8] == AI && board[i+16] == AI && board[i+24] == AI)
                    return 2;
            }
            // check if AI won on a left diagonal
            if( (i >= 3 && i <= 6) || (i >= 10 && i <= 13) || (i >= 17 && i <= 20) )
            {
                if(board[i+6] == AI && board[i+12] == AI && board[i+18] == AI)
                    return 2;
            }
        }
    }
    return 0;
}

void GameArray::clearBoard()
{
    for(int i=0; i<42; i++)
    {
        board[i] = OPEN;
    }
}
/*
0   1   2   3   4   5   6
7   8   9   10  11  12  13
14  15  16  17  18  19  20
21  22  23  24  25  26  27
28  29  30  31  32  33  34
35  36  37  38  39  40  41
*/
