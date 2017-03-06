#ifndef CELL_H
#define CELL_H

class Cell
{
    public:
        Cell(const int& i, const int& j);
        int get_x();
        int get_y();
        bool is_empty();
        void fill();
        void empty(); //Could use a setter but seems clearer
        void show();
        bool vacant;

    private:
        int x;
        int y;
};

#endif
