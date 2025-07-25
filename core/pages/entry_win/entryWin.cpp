#include "entryWin.hpp"

void EntryWin::openEntryWin()
{
    entryWin = newwin(Style::instance().term_rows(), Style::instance().term_cols(), 0, 0);

    wclear(stdscr);   // Clear the screen for page change
    wrefresh(stdscr); //

    // LOGO
    wattron(entryWin, COLOR_PAIR(1));
    int y = Style::instance().term_cols() / 7;
    int x = (Style::instance().term_cols() - Style::instance().logo_width()) / 2; // Logo'yu ortaliyozs
    std::vector<std::string> l = Style::instance().logo();
    for (std::string row : l)
        mvwprintw(entryWin, y++, x, "%s", row.c_str());
    wattroff(entryWin, COLOR_PAIR(1));

    int highlighted = 0;
    drawOptions(highlighted);
}

void EntryWin::drawOptions(int highlighted)
{

    int start_y = Style::instance().logo_height() + (Style::instance().term_cols() / 7) + 5;
    int start_x = (Style::instance().term_cols() - 20) / 2; // Center the options
    int spacing = 2;

    for (size_t i = 0; i < options.size(); ++i)
    {
        int y = start_y + i * spacing;

        if ((int)i == highlighted)
        {
            wattron(entryWin, COLOR_PAIR(2));
            mvwprintw(entryWin, y, start_x, "%s", options[i].c_str());
            wattroff(entryWin, COLOR_PAIR(2));
        }
        else
        {
            wattron(entryWin, COLOR_PAIR(1));
            mvwprintw(entryWin, y, start_x, "%s", options[i].c_str());
            wattroff(entryWin, COLOR_PAIR(1));
        }
    }
    wrefresh(entryWin);
}

void EntryWin::moveEntryWinCursor(MENU_CURSOR_MOVE direction)
{
    if (direction == MENU_CURSOR_MOVE::UP)
    {
        highlighted = (highlighted - 1 + options.size()) % options.size();
    }
    else if (direction == MENU_CURSOR_MOVE::DOWN)
    {
        highlighted = (highlighted + 1) % options.size();
    }
    drawOptions(highlighted);
}

ENTRY_CHOICE EntryWin::getChoice()
{
    switch (highlighted)
    {
    case 0:
        return ENTRY_CHOICE::FUZZY_FINDER;
    case 1:
        return ENTRY_CHOICE::NEW_FILE;
    case 2:
        return ENTRY_CHOICE::COLLABORATION;
    case 3:
        return ENTRY_CHOICE::QUIT;
    default:
        return ENTRY_CHOICE::QUIT; // Default to QUIT if something goes wrong
    }
}