#include "TetrominoZ.h"
#include "Game.h"

TetrominoZ::TetrominoZ(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoZ::rotate(const char& orientation)
{
    return true;
}

bool TetrominoZ::put_on_grid()
{
    cases[0] = game->get_cell(0, 6);
    cases[1] = game->get_cell(0, 5);
    cases[2] = game->get_cell(1, 6);
    cases[3] = game->get_cell(1, 7);
    
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
