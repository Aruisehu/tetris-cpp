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

    Game::generate();
}


void Game::play()
{

}

void Game::show()
{

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
