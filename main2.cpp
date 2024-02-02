#include <ncurses.h>
#include <string>
#include <vector>

int main()
{
    // Initialize ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    // Define strings
    std::vector<std::string> strings = {"Option 1", "Option 2", "Option 3", "exit"};

    int currentOption = 0;

    while (true)
    {
        // Print strings and connect with lines
        clear();
        for (int i = 0; i < strings.size(); ++i)
        {
            if (i == currentOption)
            {
                attron(A_REVERSE);
            }
            mvprintw(i + 1, 1, strings[i].c_str());
            attroff(A_REVERSE);

            if (i < strings.size() - 1)
            {
                mvhline(i + 2, 1, ACS_HLINE, strings[i].length());
            }
        }

        // Get user input
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            currentOption = (currentOption - 1 + strings.size()) % strings.size();
            break;
        case KEY_DOWN:
            currentOption = (currentOption + 1) % strings.size();
            break;
        case 10: // Enter key
            if (strings[currentOption] == "exit")
            {
                endwin(); // Close ncurses
                return 0; // Exit program
            }
            // Handle other options if needed
            break;
        }
    }

    endwin(); // Close ncurses

    return 0;
}
