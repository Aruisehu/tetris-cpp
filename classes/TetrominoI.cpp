#include "TetrominoI.h"

TetrominoI::TetrominoI(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoI::rotate(const char& orientation)
{
    return true;
}

void TetrominoI::put_on_grid()
{
}
