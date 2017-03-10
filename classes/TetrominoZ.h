#ifndef TETROMINO_Z_H
#define TETROMINO_Z_H
#include "Tetromino.h"

class TetrominoZ : public Tetromino
{
    public:
        TetrominoZ(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
};

#endif  
