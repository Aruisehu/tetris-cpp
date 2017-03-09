#ifndef TETROMINO_I_H
#define TETROMINO_I_H
#include "Tetromino.h"

class TetrominoI : Tetromino
{
    public:
        TetrominoI(Game& g);
        bool rotate(const char& orientation);
        void put_on_grid();
};

#endif  
