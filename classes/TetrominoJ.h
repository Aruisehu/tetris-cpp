#ifndef TETROMINO_J_H
#define TETROMINO_J_H
#include "Tetromino.h"

class TetrominoJ : public Tetromino
{
    public:
        TetrominoJ(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
};

#endif  
