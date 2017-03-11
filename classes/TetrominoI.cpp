#include "TetrominoI.h"
#include "Game.h"

TetrominoI::TetrominoI(Game& g) : Tetromino::Tetromino(g)
{
    cases = new Cell*[4];
}

bool TetrominoI::rotate(const char& orientation)
{
    Cell** new_cases = new Cell*[4];
    new_cases[0] = cases[0];
    signed int x, y;
    for (int i = 1; i < 4; i++)
    {
        if (orientation == 'L')
        {
            x = cases[i]->get_x() - cases[0]->get_x();
            y = cases[i]->get_y() - cases[0]->get_y();
            int x_abs = x < 0 ? -x : x;
            if (x_abs > y)
            {
                x = -x;
            }
            signed int mem  = y;
            y = cases[0]->get_y() + x;
            x = cases[0]->get_x() + mem;
            if (x < 0 || x > ROWS - 1 || y < 0 || y > COLUMNS - 1)
            {
                return false;
            }
            new_cases[i] = game->get_cell(x, y);
        }
        else
        {
            x = cases[i]->get_x() - cases[0]->get_x();
            y = cases[i]->get_y() - cases[0]->get_y();
            int y_abs = y < 0 ? -y: y;
            if (y_abs > x)
            {
                y = -y;
            }
            signed int mem  = y;
            y = cases[0]->get_y() + x;
            x = cases[0]->get_x() + mem;
            if (x < 0 || x > ROWS - 1 || y < 0 || y > COLUMNS - 1)
            {
                return false;
            }
            new_cases[i] = game->get_cell(x, y);
        }
        if (!new_cases[i]->is_empty())
        {
            return false;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        //cases[0] is already new_cases[0]
        cases[i] -> empty();
        cases[i] = new_cases[i];
        cases[i] -> fill();
    }

    return true;
}

bool TetrominoI::put_on_grid()
{
    /*for (int i = 0; i < 4; i++)
    {
        cases[i]->empty();
    }*/
    cases[0] = game->get_cell(1, 5);
    cases[1] = game->get_cell(0, 5);
    cases[2] = game->get_cell(2, 5);
    cases[3] = game->get_cell(3, 5);

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

void TetrominoI::put_on_next(Cell* cells[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        cases[i] = cells[1][i];
        cases[i]->fill();
    }
}
