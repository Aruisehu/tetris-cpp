#ifndef TETROMINO_O_H
#define TETROMINO_O_H
#include "Tetromino.h"

class TetrominoO : public Tetromino
{
    public:
        TetrominoO(Game& g);
        bool rotate(char const& orientation);
        bool put_on_grid();
        void put_on_next(Cell* cells[4][4]);
};

#endif  
