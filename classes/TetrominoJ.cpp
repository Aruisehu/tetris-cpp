#include "TetrominoJ.h"

TetrominoJ::TetrominoJ(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoJ::rotate(const char& orientation)
{
    return true;
}
