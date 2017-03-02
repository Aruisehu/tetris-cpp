#include <iostream>
#include "classes/Cell.h"
#include "classes/Tetromino.h"

using namespace std;

int main(void)
{
  Cell c(0, 0);
  c.show();
  c.fill();
  c.show();
  return 0;
}
