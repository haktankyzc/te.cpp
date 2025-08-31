// ===================================================
//         _______ ______    _____ _____  _____
//        |__   __|  ____|  / ____|  __ \|  __ \
//           | |  | |__    | |    | |__) | |__) |
//          | |  |  __|   | |    |  ___/|  ___/
//         | |  | |____  | |____| |    | |
//        |_|  |______|  \_____|_|    |_|
//  Project : Te.cpp
//  Author  : Haktan K.
//  Version : v0.1.0``
//  Date    : 2025-06-14
//  Desc    : Terminal Text Editor (te) for linux aims for multiple editor
//  skills like online editing with other people and vim-like skills
// ===================================================

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <ncurses.h>
#include <ostream>
#include <string>

#include "../common/styles/style.hpp"
#include "../utils/color_term.hpp"
#include "./input_handler/input_handler.hpp"
#include "./pages/editor_win/editorWin.hpp"
#include "pages/entry_win/entryWin.hpp"

#define VERSION "0.1.0"

// NOTE: SHORTCUTS
namespace fs = std::filesystem;
auto &style = Style::instance();

typedef enum PAGE {
  PAGE_ENTRY,
  PAGE_EDITOR,
  PAGE_FUZZY_SEARCH,
  PAGE_COLLABORATION
} PAGE;

PAGE current_page = PAGE_ENTRY; // NOTE: entry page

// NOTE: Opening arguments parsing
namespace Args {
enum Type {
  ARG_VERSION,
  ARG_HELP,
  ARG_CONFIG,
  ARG_FILE,
  ARG_FOLDER,
  ARG_NEW_FILE
};

Type classify(const std::string &arg) {
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

class TE : public InputHandler, public EntryWin, public EditorWin {
private:
public:
  void initTerm() {
    // Initializes ncurses and sets the terminal settings
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);

    int r, c = 0;
    getmaxyx(stdscr, r, c); // Terminal boyutunu alalim kardess
    style.updateFromWindowSize(c, r);

    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION,
              NULL); // For mouse events

    // Renkleri tanımla
    start_color();
    use_default_colors();

    //* Entry Screen Pairs
    // TODO:  Split here to style.hpp ( void initColors() and some comments )
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Sİyah üstü yeşil yazı
    init_pair(2, COLOR_BLACK, COLOR_GREEN); // Yeşil üstü siyah yazı
    init_pair(3, COLOR_WHITE, COLOR_BLACK); // Yeşil üstü siyah yazı
    init_pair(4, COLOR_BLUE, COLOR_BLACK);  // Yeşil üstü siyah yazı
  }

  int startApp(int argc, char *argv[]) {
    setlocale(LC_ALL, ""); // UTF-8 karakterler bu olmadan olmiyomis haci
    // TODO: Split here to eventmanager class (HandleArgs)
    if (argc > 1) {
      Args::Type argType = Args::classify(argv[1]);
      switch (argType) {
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
    } else { // ARG_NONE
      initTerm();
      // EntryWin::openEntryWin();
      EditorWin::init(EDITOR_OPEN_MODE::OPEN_FILE, "../common/types.hpp");
    }

    if (LINES < style.required_term_rows() ||
        COLS < style.required_term_cols()) {
      endwin();
      std::cerr << "Terminal size (" << LINES << "," << COLS << ") "
                << TERM_RED("is too small") << ". Minimum size is "
                << style.required_term_rows() << "x"
                << style.required_term_cols() << std::endl;
      return EXIT_FAILURE;
    }

    // =======================================
    // =     BASIC ENTRY WIN TEST            =
    // =======================================
    /*
    int ch;
    while ((ch = getch()) != 'q')
    {
      endwin();
      ENTRY_CHOICE choice;
      InputEvent event = InputHandler::getUserInput(ch);
      if(event.type == InputType::KEY_PRESS_DOWN){
        EntryWin::moveEntryWinCursor(MENU_CURSOR_MOVE::DOWN);
      }
      if(event.type == InputType::KEY_PRESS_UP){
        EntryWin::moveEntryWinCursor(MENU_CURSOR_MOVE::UP);
      } if(event.type == InputType::KEY_PRESS_ENTER){
        choice = getChoice();
        endwin();
        switch (choice)
        {
        case ENTRY_CHOICE::FUZZY_FINDER:
          std::cout << "Fuzzy Finder is not implemented yet.\n";
          break;
        case ENTRY_CHOICE::NEW_FILE:
          std::cout << "New File is not implemented yet.\n";
          break;
        case ENTRY_CHOICE::COLLABORATION:
          std::cout << "Collaboration is not implemented yet.\n";
          break;
        case ENTRY_CHOICE::QUIT:
          return EXIT_SUCCESS;
        }
        return EXIT_SUCCESS;
      }
      //return EXIT_SUCCESS;
    }
    */

    // =======================================
    // =     BASIC EDITOR WIN TEST         =
    // =======================================

    int ch;
    move(0, 0); // Move cursor to the top-left corner
    while ((ch = getch()) != 'q') {
      InputEvent event = InputHandler::getUserInput(ch);
      if (event.type == InputType::KEY_PRESS_UP)
        EditorWin::handleCursorMove(CURSOR_MOVEMENT::UP);
      if (event.type == InputType::KEY_PRESS_DOWN)
        EditorWin::handleCursorMove(CURSOR_MOVEMENT::DOWN);
      if (event.type == InputType::KEY_PRESS_LEFT)
        EditorWin::handleCursorMove(CURSOR_MOVEMENT::LEFT);
      if (event.type == InputType::KEY_PRESS_RIGHT)
        EditorWin::handleCursorMove(CURSOR_MOVEMENT::RIGHT);
      if (event.type == InputType::KEY_PRESS_COLON)
        std::string com = EditorWin::handleStatusBarCommand();
    }

    endwin();
    std::cout << EditorWin::cursor->col << " " << EditorWin::cursor->row
              << std::endl;
    std::cout << "` te editor..." << std::endl;
    // EditorWin::printEditorBuf();
    return EXIT_SUCCESS;
  }
};
