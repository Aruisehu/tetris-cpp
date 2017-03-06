#ifndef TETROMINO_H
#define TETROMINO_H

#include "Cell.h"

class Tetromino
{
    public:
        Tetromino();
        void rotate();
        void fall(const int& fall_rate);
        void move(const int& dir);
        static Tetromino* random();

    private:
        Cell* cases;
};

#endif
