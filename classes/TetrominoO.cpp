#include "TetrominoO.h"
#include "Game.h"

TetrominoO::TetrominoO(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoO::rotate(const char& orientation)
{
    return true; // We always can rotate a square and the result is ... itself. So no transformation needed
}

bool TetrominoO::put_on_grid()
{
    for (int i = 0; i < 4; i++)
    {
        cases[i]->empty();
    }
    cases[0] = game->get_cell(0, 5);
    cases[1] = game->get_cell(0, 4);
    cases[2] = game->get_cell(1, 5);
    cases[3] = game->get_cell(1, 4);
    
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

void TetrominoO::put_on_next(Cell* cells[4][4])
{
    cases[0] = cells[1][1];
    cases[1] = cells[1][2];
    cases[2] = cells[2][1];
    cases[3] = cells[2][2];
    for (int i = 0; i<4; i++)
    {
        cases[i] -> fill();
    }
}
