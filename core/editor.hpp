// ===================================================
//         _______ ______    _____ _____  _____
//        |__   __|  ____|  / ____|  __ \|  __ \
//           | |  | |__    | |    | |__) | |__) |
//          | |  |  __|   | |    |  ___/|  ___/
//         | |  | |____  | |____| |    | |
//        |_|  |______|  \_____|_|    |_|
//  Project : Te.cpp
//  Author  : Haktan K.
//  Version : v0.1.0
//  Date    : 2025-06-14
//  Desc    : Terminal Text Editor (te) for linux aims for multiple editor skills like online editing with other people and vim-like skills
// ===================================================

#include <ncurses.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>

#include "./status_bar/status_bar.hpp"
#include "./input_handle/input_handler.hpp"
#include "../utils/color_term.hpp"

#define VERSION "0.1.0"

const int te_cpp_logo_width = 50;
const int te_cpp_logo_height = 6;
const char *te_cpp_logo[] = {
    "████████╗███████╗         ██████╗██████╗ ██████╗ ",
    "╚══██╔══╝██╔════╝        ██╔════╝██╔══██╗██╔══██╗",
    "   ██║   █████╗          ██║     ██████╔╝██████╔╝",
    "   ██║   ██╔══╝          ██║     ██╔═══╝ ██╔═══╝ ",
    "   ██║   ███████╗███████╗╚██████╗██║     ██║     ",
    "   ╚═╝   ╚══════╝╚══════╝ ╚═════╝╚═╝     ╚═╝     ",
    nullptr};


// TODO: Split these measures to  another design file
#define PADDING_L_R 2
#define PADDING_T_B 1
#define REQUIRED_TERM_ROWS 30
#define REQUIRED_TERM_COLS 80

namespace fs = std::filesystem;

typedef enum EDITOR_MODE
{
  NORMAL,
  INSERT,
  VISUAL,
  COMMAND
} EDITOR_MODE;

typedef enum PAGE
{
  PAGE_ENTRY,
  PAGE_EDITOR,
  PAGE_FUZZY_SEARCH,
  PAGE_COLLABORATION
} PAGE;

std::vector<std::string> options = {
    "🔍  Fuzzy Finder",
    "📄  New File",
    "🤝  Collaboration",
    "🚪  Quit"
};

EDITOR_MODE current_mode = NORMAL; // NOTE: entry mode
PAGE current_page = PAGE_ENTRY;    // NOTE: entry page

namespace Args
{
  enum Type
  {
    ARG_VERSION,
    ARG_HELP,
    ARG_CONFIG,
    ARG_FILE,
    ARG_FOLDER,
    ARG_NEW_FILE
  };

  Type classify(const std::string &arg)
  {
    if (arg == "--version")
      return ARG_VERSION;
    if (arg == "--help")
      return ARG_HELP;
    if (arg == "--config")
      return ARG_CONFIG;
    if (fs::is_regular_file(arg))
      return ARG_FILE;
    if (fs::is_directory(arg))
      return ARG_FOLDER;
    return ARG_NEW_FILE;
  }

} // namespace Args

class TE
{
private:
  int TERM_ROWS = 0;
  int TERM_COLS = 0;

  WINDOW *entryWin;
  WINDOW *fuzzyWin;
  WINDOW *collabWin;
  WINDOW *editorWin;

public:
  void openEntryWin()
  {
    entryWin = newwin(TERM_ROWS, TERM_COLS, 0, 0);

    wclear(stdscr);
    wrefresh(stdscr);

    // LOGO
    wattron(entryWin, COLOR_PAIR(1));
    int y = TERM_COLS / 7;
    int x = (TERM_COLS - te_cpp_logo_width) / 2; // Logo'yu ortaliyozs
    for (int i = 0; te_cpp_logo[i] != nullptr; ++i)
      mvwprintw(entryWin, y++, x, "%s", te_cpp_logo[i]);
    wattroff(entryWin, COLOR_PAIR(1));

    int highlighted = 0;
    int choice = -1;
    int start_y = te_cpp_logo_height + (TERM_COLS / 7) + 5;
    int start_x = (TERM_COLS - 20) / 2; // Center the options
    int spacing = 2;

    while (true)
    {
      for (size_t i = 0; i < options.size(); ++i)
      {
        int y = start_y + i * spacing;

        if ((int)i == highlighted)
        {
          attron(COLOR_PAIR(1));
          mvprintw(y, start_x, "%s", options[i].c_str());
          attroff(COLOR_PAIR(1));
        }
        else
        {
          attron(COLOR_PAIR(1));
          mvprintw(y, start_x, "%s", options[i].c_str());
          attroff(COLOR_PAIR(1));
        }
      }
      wrefresh(entryWin);
      break;
    }
  }

  void initTerm()
  {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);
    getmaxyx(stdscr, TERM_ROWS, TERM_COLS); // Terminal boyutunu alalim kardess

    // Renkleri tanımla
    start_color();
    use_default_colors();

    // Entry Screen Pairs
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Sİyah üstü yeşil yazı
    init_pair(2, COLOR_BLACK, COLOR_GREEN); // Yeşil üstü siyah yazı
  }

  int startApp(int argc, char *argv[])
  {
    setlocale(LC_ALL, ""); // UTF-8 karakterler bu olmadan olmiyomis haci

    if (argc > 1)
    {
      Args::Type argType = Args::classify(argv[1]);
      switch (argType)
      {
      case Args::ARG_VERSION:
        std::cout << "te version " << VERSION << std::endl;
        return EXIT_SUCCESS;

      case Args::ARG_HELP:
        std::cout << "Usage: te [options] [file/folder]\n"
                  << "Options:\n"
                  << "  --version   Show version information\n"
                  << "  --help      Show this help message\n"
                  << "  --config    Show configuration options\n";
        return EXIT_SUCCESS;

      case Args::ARG_CONFIG:
        std::cout << "Configuration options are not implemented yet.\n";
        return EXIT_FAILURE;

      case Args::ARG_FILE:
        std::cout << "ARG_FILE open option is not implemented yet.\n";
        return EXIT_FAILURE;

      case Args::ARG_FOLDER:
        std::cout << "ARG_FOLDER open option is not implemented yet.\n";
        return EXIT_FAILURE;
      case Args::ARG_NEW_FILE:
        std::cout << "ARG_NEW_FILE open option is not implemented yet.\n";
        return EXIT_FAILURE;
      }
    }
    else
    { // ARG_NONE
      initTerm();
      openEntryWin();
    }

    if (LINES < REQUIRED_TERM_ROWS || COLS < REQUIRED_TERM_COLS)
    {
      endwin();
      std::cerr << "Terminal size (" << TERM_ROWS << "," << TERM_COLS << ")" << TERM_RED(" is too small") << ". Minimum size is " << REQUIRED_TERM_ROWS << "x" << REQUIRED_TERM_COLS << std::endl;
      return EXIT_FAILURE;
    }

    int ch;
    while ((ch = getch()) != 'q')
    {
      
    }

    endwin();
    return EXIT_SUCCESS;
  }
};
