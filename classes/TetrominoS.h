#ifndef TETROMINO_S_H
#define TETROMINO_S_H
#include "Tetromino.h"

class TetrominoS : public Tetromino
{
    public:
        TetrominoS(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
};

#endif  
