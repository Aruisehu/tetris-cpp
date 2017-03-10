#include "Tetromino.h"
#include "Game.h"
using namespace std;

Tetromino::Tetromino(Game& g)
{
    game = &g;
}

Tetromino* Tetromino::random(Game& g)
{
    Tetromino* generated;
    int rng;
    srand(time(NULL));
    rng = rand() % 7;

    switch (rng)
    {
        case 0:
            generated = new TetrominoI(g);
            break;
        case 1:
            generated = new TetrominoJ(g);
            break;
        case 2:
            generated = new TetrominoL(g);
            break;
        case 3:
            generated = new TetrominoO(g);
            break;
        case 4:
            generated = new TetrominoS(g);
            break;
        case 5:
            generated = new TetrominoT(g);
            break;
        default:
            generated = new TetrominoZ(g);
            break;
    }


    return generated;
}

bool Tetromino::rotate(const char& orientation)
{
    return true;
}

bool Tetromino::put_on_grid()
{
    return false;
}

bool Tetromino::move(const int& dir)
{
    /* 2 possible values for dir
     * 0: move left
     * 1: move right */

    //need to make separate loop, these steps must be done one
    //after an other.
    for (int i = 0; i < 4; i++)
    {
        cases[i] -> empty();
    }
    for (int i = 0; i < 4; i++)
    {
        int y = cases[i]->get_y();
        int x = cases[i]->get_x();
        x = (dir == 0) ? x-1 : x+1;
        if (x >= 0 && x < COLUMNS)
        {
            if (!game->get_cell(x, y)->is_empty())
            {
                //Fill back the cell
                for (int i = 0; i < 4; i++)
                {   
                    cases[i] -> fill();
                }
                return false;
            }
        }
        else 
        {
            //Stuck by the wall
            //Fill back the cell
            for (int i = 0; i < 4; i++)
            {   
                cases[i] -> fill();
            }
            return false;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int y = cases[i]->get_y();
        int x = cases[i]->get_x();
        x = (dir == 0) ? x-1 : x+1;
        cases[i] = game->get_cell(x, y);
        cases[i] -> fill();
    }
    return true;
}

bool Tetromino::fall()
{
    /* Return if the Tetromino can fall or not
     *(and do it if it can)*/

    for (int i = 0; i < 4; i++)
    {
        cases[i] -> empty();
    }
    for (int i = 0; i < 4; i++)
    {
        int y = cases[i]->get_y() + 1;
        int x = cases[i]->get_x();
        if (y < ROWS)
        {
            if (!game->get_cell(x, y)->is_empty())
            {
                //Fill back the cell
                for (int i = 0; i < 4; i++)
                {   
                    cases[i] -> fill();
                }
                return false;
            }
        }
        else 
        {
            //Stuck by the wall
            //Fill back the cell
            for (int i = 0; i < 4; i++)
            {   
                cases[i] -> fill();
            }
            return false;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        int y = cases[i]->get_y() + 1;
        int x = cases[i]->get_x();
        cases[i] = game->get_cell(x, y);
        cases[i] -> fill();
    }
    return true;

}

