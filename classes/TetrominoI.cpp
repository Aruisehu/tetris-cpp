#include "TetrominoI.h"
#include "Game.h"

TetrominoI::TetrominoI(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoI::rotate(const char& orientation)
{
    return true;
}

bool TetrominoI::put_on_grid()
{
    cases[0] = game->get_cell(1, 6);
    cases[1] = game->get_cell(0, 6);
    cases[2] = game->get_cell(2, 6);
    cases[3] = game->get_cell(3, 6);

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
