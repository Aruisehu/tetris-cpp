#include "TetrominoZ.h"

TetrominoZ::TetrominoZ(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoZ::rotate(const char& orientation)
{
    return true;
}

void TetrominoZ::put_on_grid()
{
}
