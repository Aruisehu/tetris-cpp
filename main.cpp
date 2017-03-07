#include <iostream>
#include <ncurses.h>
#include "classes/Cell.h"
#include "classes/Tetromino.h"
#include "classes/Game.h"

using namespace std;

int main(void)
{
    Game* play = new Game();
    play -> play();
    return 0;
}
