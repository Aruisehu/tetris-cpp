#ifndef TETROMINO_Z_H
#define TETROMINO_Z_H
#include "Tetromino.h"

class TetrominoZ : public Tetromino
{
    public:
        TetrominoZ(Game& g);
        bool rotate(const char& orientation);
        bool put_on_grid();
        void put_on_next(Cell* cells[4][4]);
};

#endif  
