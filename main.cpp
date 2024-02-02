// std::vector<std::string> strings = {"/home/ujjwal/Desktop/NcursesPG/eg", "/home/ujjwal/Desktop/NcursesPG/eg/pg", "Option 3", "Option 4"};

#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

int main()
{
    // Initialize ncurses
    initscr();
    keypad(stdscr, TRUE); // Enable keypad input
    raw();                // Disable line buffering
    noecho();             // Do not display input characters

    // List of strings
    std::vector<std::string> strings = {"eg", "eg/pg", "Option 3", "Option 4"};

    int currentRow = 0;

    while (true)
    {
        // Clear the screen
        clear();

        // Print the list of strings
        for (int i = 0; i < strings.size(); ++i)
        {
            if (i == currentRow)
            {
                // Highlight the current selected row
                attron(A_REVERSE);
                printw("%s\n", strings[i].c_str());
                attroff(A_REVERSE);
            }
            else
            {
                printw("%s\n", strings[i].c_str());
            }
        }

        // Get user input
        int key = getch();

        // Process user input
        switch (key)
        {
        case KEY_UP:
            // Move up in the list
            currentRow = (currentRow - 1 + strings.size()) % strings.size();
            break;
        case KEY_DOWN:
            // Move down in the list
            currentRow = (currentRow + 1) % strings.size();
            break;
        case 10: // Enter key
            // Exit the loop and write the selected string to a temporary file
            endwin(); // End ncurses mode
            std::ofstream tempFile("selected_directory.txt");
            if (tempFile.is_open())
            {
                tempFile << strings[currentRow];
                tempFile.close();
            }
            else
            {
                std::cerr << "Error: Unable to write to temporary file" << std::endl;
                return EXIT_FAILURE;
            }
            return EXIT_SUCCESS;
        }
    }

    // End ncurses mode
    endwin();

    return EXIT_SUCCESS;
}
