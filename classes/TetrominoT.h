#ifndef TETROMINO_T_H
#define TETROMINO_T_H
#include "Tetromino.h"

class TetrominoT : Tetromino
{
    public:
        TetrominoT(Game& g);
        bool rotate(const char& orientation);
};

#endif  
