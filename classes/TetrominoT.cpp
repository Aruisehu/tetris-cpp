#include "TetrominoT.h"
#include "Game.h"

TetrominoT::TetrominoT(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoT::rotate(const char& orientation)
{
    return true;
}

bool TetrominoT::put_on_grid()
{
    cases[0] = game->get_cell(0, 6);
    cases[1] = game->get_cell(0, 7);
    cases[2] = game->get_cell(0, 5);
    cases[3] = game->get_cell(1, 6);
    
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
