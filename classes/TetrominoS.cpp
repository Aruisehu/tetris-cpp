#include "TetrominoS.h"

TetrominoS::TetrominoS(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoS::rotate(const char& orientation)
{
    return true;
}
