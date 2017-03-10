#ifndef TETROMINO_I_H
#define TETROMINO_I_H
#include "Tetromino.h"

class TetrominoI : public Tetromino
{
    public:
        TetrominoI(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
};

#endif  
