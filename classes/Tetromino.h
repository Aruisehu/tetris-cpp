#ifndef TETROMINO_H
#define TETROMINO_H

#include "Cell.h"
#include <iostream>

class Game; //Here's for you little compiler

class Tetromino
{
    public:
        Tetromino(Game& g);
        virtual bool rotate(const char& orientation);
        bool fall(const int& fall_rate);
        bool move(const int& dir);
        static Tetromino* random(Game& g);

    protected:
        Cell** cases;
        Game* game;
};

#endif
