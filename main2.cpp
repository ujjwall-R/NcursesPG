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

    // Define rows with strings
    std::vector<std::vector<std::string>> rows = {
        {"Option 1", "Option 2", "Option 3"},
        {"Option 4", "Option 5", "Option 6"},
        {"Option 7", "Option 8", "exit"}};

    int currentRow = 0;
    int currentOption = 0;

    while (true)
    {
        // Print rows and strings
        clear();
        for (int i = 0; i < rows.size(); ++i)
        {
            for (int j = 0; j < rows[i].size(); ++j)
            {
                if (i == currentRow && j == currentOption)
                {
                    attron(A_REVERSE);
                }
                mvprintw(i + 1, j * 15, rows[i][j].c_str());
                attroff(A_REVERSE);

                if (j < rows[i].size() - 1)
                {
                    mvhline(i + 1, (j + 1) * 15 - 1, ACS_VLINE, 3); // Vertical lines between options
                }
            }
        }

        // Get user input
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            currentRow = (currentRow - 1 + rows.size()) % rows.size();
            break;
        case KEY_DOWN:
            currentRow = (currentRow + 1) % rows.size();
            break;
        case KEY_LEFT:
            currentOption = (currentOption - 1 + rows[currentRow].size()) % rows[currentRow].size();
            break;
        case KEY_RIGHT:
            currentOption = (currentOption + 1) % rows[currentRow].size();
            break;
        case 10: // Enter key
            if (rows[currentRow][currentOption] == "exit")
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
