#include <iostream>
#include "Cell.h"

Cell::Cell(const int& i, const int& j) :
  x(i), y(j)
{
  vacant = true;
}

int Cell::get_x() { return x; }
int Cell::get_y() { return y; }
bool Cell::is_empty() { return vacant; }
void Cell::fill() { vacant = false; }
void Cell::empty() { vacant = true; }

void Cell::show()
{
  std::string c = Cell::is_empty() ? " " : "\u2588";
  std::cout << c;
}
