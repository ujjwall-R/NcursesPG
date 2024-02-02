#include <ncurses.h>

int main()
{
    // Initialize ncurses
    initscr();

    // Enable special characters (like line-drawing characters)
    keypad(stdscr, TRUE);
    raw();

    // Print '└──' to the screen
    addch(ACS_LLCORNER); // '└'
    addch(ACS_HLINE);    // '─'
    addch(ACS_HLINE);    // '─'

    // Refresh the screen
    refresh();

    // Wait for user input before closing
    getch();

    // Clean up and close ncurses
    endwin();

    return 0;
}
