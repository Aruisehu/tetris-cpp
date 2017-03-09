#include "TetrominoO.h"

TetrominoO::TetrominoO(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoO::rotate(const char& orientation)
{
    return true; // We always can rotate a square and the result is ... itself. So no transformation needed
}

