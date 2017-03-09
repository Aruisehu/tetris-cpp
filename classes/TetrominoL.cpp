#include "TetrominoL.h"

TetrominoL::TetrominoL(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoL::rotate(const char& orientation)
{
    return true; 
}

void TetrominoL::put_on_grid()
{
}
