#ifndef GAMEARRAY_H
#define GAMEARRAY_H

using namespace std;

class GameArray
{
public:
    GameArray();
    int checkGameOver();
    bool isColumnFull(int column);          // check to see if a column is full, whether a piece can be placed there
    int getPositionPlayer1(int column);     // get the array number where a piece will fall
    int getPositionPlayer2(int column);
    void clearBoard();                      // clear board back to initial state (0)
    int getArrayVal(int pos);

private:
    int board[42];      // will use this to store positions of each piece to find who wins, 7 columns 6 rows
};

#endif
