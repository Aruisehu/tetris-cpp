#ifndef TETROMINO_S_H
#define TETROMINO_S_H
#include "Tetromino.h"

class TetrominoS : Tetromino
{
    public:
        TetrominoS(Game& g);
        bool rotate(const char& orientation);
        void put_on_grid();
};

#endif  
