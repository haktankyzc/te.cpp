#include "status_bar.hpp"

static WINDOW *draw_status_bar(WINDOW *parentWIN)
{

    int width = COLS;
    int height = 1;
    int starty = LINES - 1;

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    WINDOW *bar = derwin(parentWIN, height, width, starty, 0);
    wbkgd(bar, COLOR_PAIR(1));
    werase(bar);

    mvwprintw(bar, 0, 0, "Mode: NORMAL");
    mvwprintw(bar, 0, 20, "Status: READY");
    mvwprintw(bar, 0, 45, "Press ':' to enter command");

    wrefresh(bar);
    return bar;
}

static std::string get_command_input(WINDOW *bar, int *cancelled)
{
    std::string input;

    werase(bar);
    wmove(bar, 0, 0);
    wrefresh(bar);

    echo();
    curs_set(1);
    mvwprintw(bar, 0, 0, ":");
    wrefresh(bar);

    int ch;
    while ((ch = wgetch(bar)) != '\n')
    {
        if (ch == 27)
        { // ESC key
            *cancelled = 1;
            break;
        }
        else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
                int len = input.size();
                mvwprintw(bar, 0, len + 1, " ");
                wmove(bar, 0, len + 1);
                wrefresh(bar);
            }
        }
        else if (input.size() < MAX_CMD_BAR_INPUT_L - 1 && ch >= 32 && ch <= 126)
        {
            input.push_back(ch);
            mvwprintw(bar, 0, input.size(), "%c", ch);
            wrefresh(bar);
        }
    }

    noecho();
    curs_set(0);
    werase(bar);
    wrefresh(bar);

    if (*cancelled)
    {
        return "";
    }

    return input;
}