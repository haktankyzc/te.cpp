#ifndef ENTRY_WIN_HPP
#define ENTRY_WIN_HPP

#include <string>
#include <ncurses.h>
#include <vector>

#include "../../../common/styles/style.hpp"

typedef enum class MENU_CURSOR_MOVE
{
    UP,
    DOWN,
} MENU_CURSOR_MOVE;

typedef enum class CHOICE
{
    FUZZY_FINDER,
    NEW_FILE,
    COLLABORATION,
    QUIT
} ENTRY_CHOICE;

class EntryWin
{
private:
    WINDOW *entryWin;

    std::vector<std::string> options = {
        "🔍  Fuzzy Finder",
        "📄  New File",
        "🤝  Collaboration",
        "🚪  Quit"};

    void drawOptions(int highlighted);
public:
    void openEntryWin();
    void moveEntryWinCursor(MENU_CURSOR_MOVE direction);
    ENTRY_CHOICE getChoice();

    int highlighted = 0; //Chosen option index
};

#endif // ENTRY_WIN_HPP