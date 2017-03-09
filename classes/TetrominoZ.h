#ifndef TETROMINO_Z_H
#define TETROMINO_Z_H
#include "Tetromino.h"

class TetrominoZ : Tetromino
{
    public:
        TetrominoZ(Game& g);
        bool rotate(const char& orientation);
};

#endif  
