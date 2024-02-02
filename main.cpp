#include <cstring>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>

struct DTreeNode
{
    std::string name;
    std::string path;
    std::vector<DTreeNode *> children;
};

class PrintDree
{
private:
    DTreeNode *selectedNode; // Keep track of the selected node

public:
    PrintDree() : selectedNode(nullptr) {}

    void printTree(DTreeNode *root)
    {
        initscr();
        keypad(stdscr, TRUE);
        noecho();
        curs_set(0);
        dfs(root, 0, 0, true, 0);
        refresh();
        handleInput(root);
        endwin();

        // After ncurses, change to the selected directory if available
        if (selectedNode != nullptr)
        {
            navigateToDirectory(selectedNode);
        }
    }

private:
    void dfs(DTreeNode *node, long long depth, long long currentDepth, bool isLastChild, long long mask)
    {
        for (long long i = 0; i < currentDepth; i++)
        {
            if (((mask >> i) & 1ll) == 0ll)
                printw("│    ");
            else
                printw("     ");
        }
        isLastChild ? printw("└── ") : printw("├── ");

        printw("%s\n", node->name.c_str());

        for (size_t i = 0; i < node->children.size(); i++)
        {
            DTreeNode *child = node->children[i];
            if (i == node->children.size() - 1)
            {
                mask = mask | (1ll << (currentDepth + 1));
            }
            dfs(child, depth, currentDepth + 1, i == node->children.size() - 1, mask);
        }
    }

    void handleInput(DTreeNode *root)
    {
        int ch;
        long long selectedNodeIndex = 0;

        while ((ch = getch()) != KEY_F(1))
        {
            switch (ch)
            {
            case KEY_UP:
                if (selectedNodeIndex > 0)
                {
                    selectedNodeIndex--;
                }
                break;
            case KEY_DOWN:
                if (selectedNodeIndex < root->children.size() - 1)
                {
                    selectedNodeIndex++;
                }
                break;
            case 10:                                              // Enter key
                selectedNode = root->children[selectedNodeIndex]; // Store the selected node
                return;                                           // Exit the program after storing the selection
            }

            clear();
            dfs(root, 0, 0, true, 0);

            attron(A_REVERSE);
            mvprintw(selectedNodeIndex + 1, 0, "%s", root->children[selectedNodeIndex]->name.c_str());
            attroff(A_REVERSE);

            refresh();
        }
    }

    void navigateToDirectory(DTreeNode *node)
    {
        if (chdir(node->path.c_str()) == 0)
        {
            endwin(); // Close curses before launching shell

            // Use execvp to run the shell and then exit
            char *const args[] = {strdup("zsh"), nullptr};
            if (execvp("zsh", args) == -1)
            {
                std::cerr << "Error executing zsh" << std::endl;
                exit(EXIT_FAILURE); // Exit the program if execvp fails
            }
        }
        else
        {
            std::cerr << "Error changing directory to: " << node->path << std::endl;
            exit(EXIT_FAILURE); // Exit the program if changing directory fails
        }
    }
};

int main()
{
    DTreeNode *root = new DTreeNode{"Root", "/home/ujjwal/Desktop/NcursesPG"};
    root->children.push_back(new DTreeNode{"eg", "/home/ujjwal/Desktop/NcursesPG/eg"});
    root->children.push_back(new DTreeNode{"eg1", "/home/ujjwal/Desktop/NcursesPG/eg1"});
    root->children[0]->children.push_back(new DTreeNode{"pg", "/home/ujjwal/Desktop/NcursesPG/pg"});
    root->children[1]->children.push_back(new DTreeNode{"pg1", "/home/ujjwal/Desktop/NcursesPG/pg1"});

    PrintDree printer;
    printer.printTree(root);

    return 0;
}
