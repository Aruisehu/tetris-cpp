#include <iostream>
#include <ncurses.h>
#include <cstdio>
#include <ctime>
#include <string>
#include "Game.h"
#include <unistd.h>

using namespace std;

const unsigned int microseconds = 160; // how much delays to wait for each frame
const unsigned int delay = 1000; // microseconds

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

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            cases_next[i][j] = new Cell(i, j);
        }
    }

    Game::generate(); // Prepare the first tetromino
}

void Game::play()
{
    setlocale(LC_ALL, ""); // Permit the use of special unicode characters
    //need to be called before initscr();

    initscr(); // Initialize screen

    field = newwin(40, 26, 0, 0);
    info = newwin(20, 40, 3, 28);
    errors = newwin(20, 40, 3, 48);

    cbreak(); // Disable input buffering
    noecho(); // Disable automatic encoding
    nodelay(stdscr, TRUE); // Set input as non blocking
    keypad(stdscr, TRUE); // Capture special keystrokes
    curs_set(0); // Remove cursor since it's a game
    start_color(); // Start ncurses color engine

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    bool playing = true;
    bool turn = true;
    bool accelerator = false;

    double time_per_turn = 2000;
    double modifier = 1.1;

    Game::next_tetromino(); // Charge next tetromino and generate the next one
    current -> put_on_grid();

    while (playing)
    {
        turn = true;

        clock_t start_time = clock(); // Time at the start of the turn

        while(turn)
        {
            Game::show();

            // Actual time
            clock_t current_time = clock();

            // Difference between actual time and the start of the turn
            double time_diff = (double) ( current_time - start_time ) / CLOCKS_PER_SEC * 160000.0;

            if ((time_diff >= time_per_turn) || (accelerator)) // if the turn is finished
            {
                if (!Game::fall()) // If the tetromino cannot fall
                {
                    Game::empty_lines(); // Remove completed lines, increase score for each and drop other lines

                    if (Game::lose())
                    {
                        playing = false;
                    }

                    if ( score / 100 > level  )
                    {
                        // increase speed for next level
                        if ( time_per_turn > 100 ) // Speed and level cap
                        {
                            time_per_turn = time_per_turn / modifier;
                            level++; // Increment level by 1
                        }
                    }
                }

                turn = false; // end turn
            }

            //wprintw( errors, " ");
            //wprintw( errors, std::to_string(current_time).c_str());
            //wprintw( errors, " ");
            //wprintw( errors, std::to_string(time_per_turn).c_str());
            //wprintw( errors, " ");
            //wprintw( errors, std::to_string(start_time).c_str());
            //wprintw( errors, " ");
            //wprintw( errors, std::to_string(time_diff).c_str());
            //wrefresh( errors );

            int time_to_wait = (accelerator) ? microseconds / 16 : microseconds;

            accelerator = false;

            for(int i = 0; i < time_to_wait; i++) // In order to limit framerate to get 3% cpu usage instead of 100%...
            {
                usleep(delay);
                int ch = getch(); // To increase the rate at wich inputs are takens
                switch (ch) {
                    case 'H': /* user pressed key 'H' or 'h' */
                    case 'h':
                        Game::help();
                        break;
                    case KEY_LEFT:
                        current -> move(0); // Left
                        break;
                    case KEY_RIGHT:
                        current -> move(1); // Right
                        break;
                    case 'q':
                    case 'Q':
                        current -> rotate('L'); // +90°
                        break;
                    case 'd':
                    case 'D':
                        current -> rotate('R'); // -90°
                        break;
                    case KEY_DOWN:
                        current -> fall();
                        break;
                }
            }
        }
    }

    endwin(); // Reset terminal
}

void Game::show()
{
    // Reset terminal screen
    wclear( field );
    wclear( info );
    //wclear( errors );

    // FIELD
    wprintw( field, "       SUPTETRIS\n\n" );
    wattron( field, COLOR_PAIR(4) );
    for(int i = 0; i < ROWS + 2; i++)
    {
        wprintw( field, "\u2588");
    }

    wprintw( field, "\n" );

    for(int i = 0; i < ROWS; i++)
    {
        wprintw( field, "\u2588\u2588");

        wattroff( field, COLOR_PAIR(4) );

        for(int j = 0; j < COLUMNS; j++)
        {
            if (cases[i][j] -> is_empty() )
            {
                wprintw( field,"  ");
            }
            else
            {
                wprintw( field,"\u2588\u2588");
            }
        }


        wattron( field, COLOR_PAIR(4) );

        wprintw( field,"\u2588\u2588\n");
    }

    wattron( field, COLOR_PAIR(4) );

    for(int i = 0; i < ROWS + 2; i++)
    {
        wprintw( field, "\u2588");
    }

    wattroff( field, COLOR_PAIR(4) );

    // INFO
    std::string s = "Score: " + std::to_string(score) + "\n";
    wprintw( info, s.c_str() );

    s = "Level: " + std::to_string(level) + "\n\n";
    wprintw( info, s.c_str() );

    s = "Next:\n\n";
    wprintw( info, s.c_str() );

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (cases_next[i][j] -> is_empty() )
            {
                wprintw( info,"  ");
            }
            else
            {
                wprintw( info,"\u2588\u2588");
            }
        }
        wprintw( info, "\n");
    }

    wrefresh(field); // Refresh field
    wrefresh(info); // Refresh info
}

void Game::help() {
    bool help = true;

    int ch;
    while(help)
    {
        wclear( field );
        wclear( info );

        // Display help
        wprintw( field, "      HELP\n\n");
        wprintw( field, "tetromino L\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n\n");
        wprintw( field, "tetromino J\n");
        wprintw( field, "    \u2588\u2588\n");
        wprintw( field, "    \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n\n");
        wprintw( field, "tetromino O\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n\n");
        wprintw( field, "tetromino S\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n");
        wprintw( field, "    \u2588\u2588\n\n");
        wprintw( field, "tetromino Z\n");
        wprintw( field, "    \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\n\n");
        wprintw( field, "tetromino I\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\n");
        wprintw( field, "  \u2588\u2588\n\n");
        wprintw( field, "tetromino T\n");
        wprintw( field, "  \u2588\u2588\u2588\u2588\u2588\u2588\n");
        wprintw( field, "    \u2588\u2588\n");

        wprintw( info, "Tetris is a game where you create lines of block using tetrominos.\n");
        wprintw( info, "Use the left arrow and right arrow keys\nto rotate the falling tetromino.\n\n");
        wprintw( info, "The score is incremented by 10 for each completed lines\n");
        wprintw( info, "Each completed lines disapear.\n\n");
        wprintw( info, "If the placed tetrominos touch the top\nof the playfield it's the end.\n\n");
        wprintw( info, "Push any key to continue playing");

        wrefresh( field );
        wrefresh( info );

        for(int i = 0; i < 160; i++) // In order to limit framerate to get 3% cpu usage instead of 100%...
        {
            ch = getch();
            if (ch != ERR)
            {
                help = false;
            }
            usleep(1000);
        }
    }
}

bool Game::line_filled(const int& row)
{
    for(int j = 0; j < COLUMNS; j++)
    {
        if (cases[row][j] -> is_empty())
        {
            return false;
        }
    }

    return true;
}

void Game::empty_line(const int& row)
{
    for(int j = 0; j < COLUMNS; j++)
    {
        cases[row][j] -> empty();
    }

    Game::drop(row);
    score += 10;
}

void Game::empty_lines()
{
    for(int i = 0; i < ROWS; i++)
    {
        if (Game::line_filled(i))
        {
            Game::empty_line(i);
        }
    }
}

void Game::drop(const int& row)
{
    for(int i = 0; i < row - 1; i++) // -1 to prevent index out of range
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            cases[row - i][j] -> vacant = cases[row - i - 1][j] -> vacant;
        }
    }

    for(int j = 0; j < COLUMNS; j++) // Reset last line which will always be empty after a drop
    {
        cases[0][j] -> empty();
    }
}

bool Game::lose()
{
    Game::next_tetromino();
    next -> put_on_next(cases_next);
    return !current -> put_on_grid();
}

bool Game::fall()
{
    // Make current fall if there is no obstacles
    return current -> fall();
}

void Game::generate()
{
    next = Tetromino::random(*this);
}

void Game::next_tetromino() {
    current = next;
    Game::generate();
}

Cell* Game::get_cell(const int& x, const int& y)
{
    return cases[x][y];
}
