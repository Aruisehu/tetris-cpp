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
        void play();
        void show();
        void empty_lines();
        void generate(); // Generate next Tetromino
        void next_tetromino(); // Put next tetromino in current

    private:
        void drop(const int& row); //Use to make the line fall after a line is completed. To use in empty_line()
        bool line_filled(const int& row);
        void empty_line(const int& row);
        int score, level;
        Cell*** cases;
        Tetromino* current;
        Tetromino* next;

        WINDOW* field;
        WINDOW* info;

};

#endif
