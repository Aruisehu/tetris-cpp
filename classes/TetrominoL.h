#ifndef TETROMINO_L_H
#define TETROMINO_L_H
#include "Tetromino.h"

class TetrominoL : Tetromino
{
    public:
        TetrominoL(Game& g);
        bool rotate(const char& orientation);
};

#endif  
