#ifndef TETROMINO_O_H
#define TETROMINO_O_H
#include "Tetromino.h"

class TetrominoO : public Tetromino
{
    public:
        TetrominoO(Game& g);
        bool rotate(char const& orientation);
        void put_on_grid();
};

#endif  
