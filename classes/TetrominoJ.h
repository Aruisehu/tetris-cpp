#ifndef TETROMINO_J_H
#define TETROMINO_J_H
#include "Tetromino.h"

class TetrominoJ : Tetromino
{
    public:
        TetrominoJ(Game& g);
        bool rotate(const char& orientation);
};

#endif  
