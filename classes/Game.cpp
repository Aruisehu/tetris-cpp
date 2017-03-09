#include "Game.h"
#include <unistd.h>

using namespace std;

unsigned int microseconds = 16000;

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

    Game::generate(); // Prepare the first tetromino
}

void Game::play()
{
    setlocale(LC_ALL, ""); // Permit the use of special unicode characters
    //need to be called before initscr();

    initscr(); // Initialize screen

    field = newwin(40, 26, 0, 0);
    info = newwin(20, 40, 3, 28);

    cbreak(); // Disable input buffering
    noecho(); // Disable automatic encoding
    nodelay(stdscr, TRUE); // Set input as non blocking
    keypad(stdscr, TRUE); // Capture special keystrokes
    curs_set(0); // Remove cursor since it's a game

    bool playing = true;
    bool turn = true;

    double time_per_turn = 1000;
    double modifier = 1.1;

    Game::next_tetromino(); // Charge next tetromino and generate the next one

    while (playing)
    {
        turn = true;

        clock_t start_time = clock(); // Time at the start of the turn

        while(turn)
        {
            Game::show();

            int ch = getch();
            switch (ch) {
                case 'H': /* user pressed key 'H' or 'h' */
                case 'h':
                    Game::help();
                    break;
                case KEY_LEFT:
                    //current -> rotate("left"); // +90°
                    break;
                case KEY_RIGHT:
                    //current -> rotate("right"); // -90°
                    break;
                case KEY_DOWN:
                    break;
            }

            clock_t current_time = clock(); // Actual time

            // Difference between actual time and the start of the turn
            double time_diff = (double) ( current_time - start_time ) / CLOCKS_PER_SEC * 1000.0;

            if (time_diff >= time_per_turn) // if the turn is finished
            {
                if (!Game::fall()) // If the tetromino cannot fall
                {
                    Game::next_tetromino(); //Charge the next one
                    Game::empty_lines(); // Remove completed lines, increase score for each and drop other lines

                    if (Game::lose())
                    {
                        playing = false;
                    }

                    if ( score / 100 > level  )
                    {
                        // increase speed for next level
                        if ( time_per_turn > 200 ) // Speed and level cap
                        {
                            time_per_turn = time_per_turn / modifier;
                            level++; // Increment level by 1
                        }
                    }
                }

                turn = false; // end turn
            }

            usleep(microseconds);
        }
    }

    endwin(); // Reset terminal
}

void Game::show()
{
    // Reset terminal screen
    wclear( field );
    wclear( info );

    // FIELD
    wprintw( field, "      SUPTETRIS\n\n" );
    for(int i = 0; i < 24; i++)
    {
        wprintw( field, "\u2588");
    }

    wprintw( field, "\n" );

    for(int i = 0; i < ROWS; i++)
    {
        wprintw( field, "\u2588\u2588");

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

        wprintw( field,"\u2588\u2588\n");
    }

    for(int i = 0; i < 24; i++)
    {
        wprintw( field, "\u2588");
    }

    // INFO
    std::string s = "Score: " + std::to_string(score) + "\n";
    wprintw( info, s.c_str() );

    s = "Level: " + std::to_string(level) + "\n\n";
    wprintw( info, s.c_str() );

    s = "Next:\n\n";
    wprintw( info, s.c_str() );

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

        ch = getch();
        if (ch != ERR)
        {
            help = false;
        }

        usleep(microseconds);
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
    return false; // TODO
}

bool Game::fall()
{
    // Make current fall if there is no obstacles
    return true; // TODO
}

void Game::generate()
{
    next = Tetromino::random(*this);
}

void Game::next_tetromino() {
    current = next;
    Game::generate();
}
