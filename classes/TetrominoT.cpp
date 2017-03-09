#include "TetrominoT.h"

TetrominoT::TetrominoT(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoT::rotate(const char& orientation)
{
    return true;
}
