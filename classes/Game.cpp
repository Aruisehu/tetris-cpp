#include <iostream>
#include <ncurses.h>
#include "Game.h"

using namespace std;

Game::Game()
{
  score = 0;
  cases = new Cell**[ROWS];
  for(int i = 0; i < ROWS; i++)
  {
    cases[i] = new Cell*[COLUMNS];
    for(int j = 0; j < COLUMNS; j++) 
    {
      cases[i][j] = new Cell(i, j);
    }
  }
  //TODO create tetromino using Game::generate()
}
