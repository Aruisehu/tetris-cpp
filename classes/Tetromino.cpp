#include "Tetromino.h"
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
    rng = rng % 7;

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

void Tetromino::put_on_grid()
{
}
