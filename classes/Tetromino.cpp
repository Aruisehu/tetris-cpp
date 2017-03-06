#include <iostream>
#include "Tetromino.h"
#include "Cell.h"

Tetromino::Tetromino()
{
    cases = new Cell[4] { {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    int i;
    for (i = 0; i < 4; i++)
    {
        cases[i].fill();
    }
}

