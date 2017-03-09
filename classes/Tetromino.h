#ifndef TETROMINO_H
#define TETROMINO_H

#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class Game; //Here's for you little compiler

class Tetromino
{
    public:
        Tetromino(Game& g);
        virtual bool rotate(const char& orientation);
        virtual void put_on_grid();
        bool fall(const int& fall_rate);
        bool move(const int& dir);
        static Tetromino* random(Game& g);

    protected:
        Cell** cases;
        Game* game;
};

#include "TetrominoI.h"
#include "TetrominoJ.h"
#include "TetrominoL.h"
#include "TetrominoO.h"
#include "TetrominoS.h"
#include "TetrominoT.h"
#include "TetrominoZ.h"

#endif
