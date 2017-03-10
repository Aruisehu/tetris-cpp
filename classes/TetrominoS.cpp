#include "TetrominoS.h"
#include "Game.h"

TetrominoS::TetrominoS(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoS::rotate(const char& orientation)
{
    return true;
}

bool TetrominoS::put_on_grid()
{
    cases[0] = game->get_cell(0, 6);
    cases[1] = game->get_cell(0, 7);
    cases[2] = game->get_cell(1, 6);
    cases[3] = game->get_cell(1, 5);
    
    for (int i = 0; i < 4; i++)
    {
        if (!cases[i]->is_empty())
        {
            return false;
        }
        cases[i]->fill();
    }   
    return true;
}
