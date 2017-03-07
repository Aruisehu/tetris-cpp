#include <iostream>
#include <ncurses.h>
#include "Game.h"

using namespace std;

Game::Game()
{
    score = 0;
    cases = new Cell**[ROWS];
    for(int i = 0; i < ROWS; i++)
    {
        cases[i] = new Cell*[COLUMNS];
        for(int j = 0; j < COLUMNS; j++)
        {
            cases[i][j] = new Cell(i, j);
        }
    }

    Game::generate(); // Prepare the first tetromino
}


void Game::play()
{
    setlocale(LC_ALL, "");

    initscr(); // Initialize screen

    field = newwin(26, 24, 0, 0);
    info = newwin(10, 20, 3, 28);

    cbreak(); // Disable input buffering
    noecho(); // Disable automatic encoding
    nodelay(stdscr, TRUE); // Set input as non blocking
    keypad(stdscr, TRUE); // Capture special keystrokes

    bool playing = true;
    bool turn = true;

    while (playing)
    {
        turn = true;
        Game::next_tetromino(); // Charge next tetromino
        Game::generate(); // Generate next tetromino

        curs_set(0);

        Game::show();

        wrefresh(field); // Refresh field
        wrefresh(info); // Refresh info

        while(turn)
        {
            // Fetch input data and turn the block
            // ( left arrow: -90°, right arrow: +90°, bottom arrow: speed multiplyer )

            // Wait for tic then make the block fall

        }
    }

    endwin(); // Reset terminal
}

void Game::show()
{
    // FIELD
    wprintw( field, "      SUPTETRIS\n\n" );
    for(int i = 0; i < 22; i++)
    {
        wprintw( field, "\u2588");
    }

    wprintw( field, "\n" );

    for(int i = 0; i < ROWS; i++)
    {
        wprintw( field, "\u2588");

        for(int j = 0; j < COLUMNS; j++)
        {
            if (cases[i][j] -> is_empty() )
            {
                wprintw( field,"  ");
            }
            else
            {
                wprintw( field,"\u2588\u2588");
            }
        }

        wprintw( field,"\u2588\n");
    }

    for(int i = 0; i < 22; i++)
    {
        wprintw( field, "\u2588");
    }

    // INFO
    std::string s = "Score: " + std::to_string(score) + "\n";
    wprintw( info, s.c_str() );

    s = "Level: " + std::to_string(level) + "\n\n";
    wprintw( info, s.c_str() );

    s = "Next:\n\n";
    wprintw( info, s.c_str() );

    

}

bool Game::line_filled(const int& row)
{
    for(int j = 0; j < COLUMNS; j++)
    {
        if (cases[row][j] -> is_empty())
        {
            return false;
        }
    }

    return true;
}

void Game::empty_line(const int& row)
{
    for(int j = 0; j < COLUMNS; j++)
    {
        cases[row][j] -> empty();
    }

    Game::drop(row);
    score += 10;
}

void Game::empty_lines()
{
    for(int i = 0; i < ROWS; i++)
    {
        if (Game::line_filled(i))
        {
            Game::empty_line(i);
        }
    }
}

void Game::drop(const int& row)
{
    for(int i = 0; i < row - 1; i++) // -1 to prevent index out of range
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            cases[row - i][j] -> vacant = cases[row - i - 1][j] -> vacant;
        }
    }

    for(int j = 0; j < COLUMNS; j++) // Reset last line which will always be empty after a drop
    {
        cases[0][j] -> empty();
    }
}

void Game::generate()
{
    next = Tetromino::random();
}

void Game::next_tetromino() {
    current = next;
    Game::generate();
}
