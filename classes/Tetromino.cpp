#include "Tetromino.h"

Tetromino::Tetromino(Game& g)
{
    game = &g;
}

Tetromino* Tetromino::random(Game& g)
{
    Tetromino* generated = new Tetromino(g);

    return generated;
}

bool Tetromino::rotate(const char& orientation)
{
    return true;
}
