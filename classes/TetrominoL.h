#ifndef TETROMINO_L_H
#define TETROMINO_L_H
#include "Tetromino.h"

class TetrominoL : public Tetromino
{
    public:
        TetrominoL(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
        void put_on_next(Cell* cells[4][4]);
};

#endif  
