#ifndef GAME_H
#define GAME_H
#include "Cell.h"
#include "Tetromino.h"
//Define preprocessor constants can be used in Game.cpp
#define ROWS 22 
#define COLUMNS 10

class Game
{
    public:
        Game();
        void show();
        bool line_filled(const int& row);
        void empty_line();
        void generate(); // Generate next Tetromino
        void next_tetromino(); // Put next tetromino in current

    private:
        void drop(); //Use to make the line fall after a line is completed. To use in empty_line()
        int score;
        Cell*** cases;
        Tetromino* current;
        Tetromino* next;

};

#endif
