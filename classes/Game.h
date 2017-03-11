#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <string>
#include "Tetromino.h"
#include "Cell.h"

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
        void help(); // Display help
        bool lose(); // Verify if the player losed
        bool fall(); // Make the tetromino fall if it can and return if it can
        Cell* get_cell(const int& x, const int& y);

    private:
        void drop(const int& row); //Use to make the line fall after a line is completed. To use in empty_line()
        bool line_filled(const int& row);
        void empty_line(const int& row);
        int score, level;
        Cell*** cases;
        Cell* cases_next[4][4];
        Tetromino* current;
        Tetromino* next;

        WINDOW* field;
        WINDOW* info;
        WINDOW* errors;

};

#endif
