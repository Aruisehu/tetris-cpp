#ifndef TETROMINO_T_H
#define TETROMINO_T_H
#include "Tetromino.h"

class TetrominoT : public Tetromino
{
    public:
        TetrominoT(Game& g);
        bool rotate(const char& orientation);
        void put_on_grid();
};

#endif  
