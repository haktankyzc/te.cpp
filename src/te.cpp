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
//  Desc    : Terminal Text Editor (te) for linux
// ===================================================

#include <ncurses.h>

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#define VERSION "0.1.0"

#define PADDING_L_R 2
#define PADDING_T_B 1

#define MAX_CMD_BAR_INPUT_L 100

namespace fs = std::filesystem;

enum EDITOR_MODE {
  NORMAL,
  INSERT,
  VISUAL,
  COMMAND
};

enum ArgvType {
  ARG_NONE,
  ARG_VERSION,
  ARG_HELP,
  ARG_CONFIG,
  ARG_FILE,
  ARG_FOLDER,
  ARG_NEW_FILE
};

ArgvType classifyArgv(const std::string& arg) {
  if (arg == "--version") return ARG_VERSION;
  if (arg == "--help") return ARG_HELP;
  if (arg == "--config") return ARG_CONFIG;
  if (fs::is_regular_file(arg)) return ARG_FILE;
  if (fs::is_directory(arg)) return ARG_FOLDER;
  return ARG_NEW_FILE;
}

class StatusBar {
  public:
    static WINDOW* draw_status_bar() {
  
      int width = COLS;
      int height = 1;
      int starty = LINES - 1;
  
      start_color();
      init_pair(1, COLOR_WHITE, COLOR_BLACK);
  
      WINDOW *bar = newwin(height, width, starty, 0);
      wbkgd(bar, COLOR_PAIR(1));
      werase(bar);
  
      mvwprintw(bar, 0, 0,   "Mode: NORMAL");
      mvwprintw(bar, 0, 20,  "Status: READY");
      mvwprintw(bar, 0, 45,  "Press ':' to enter command");
  
      wrefresh(bar);
      return bar;
    }
  
    static std::string get_command_input(WINDOW *bar, int* cancelled) {
      std::string input;
  
      werase(bar);
      wmove(bar, 0, 0);
      wrefresh(bar);
  
      echo();
      curs_set(1);
      mvwprintw(bar, 0, 0, ":");
      wrefresh(bar);
  
      int ch;
      while ((ch = wgetch(bar)) != '\n') {
          if (ch == 27) {  // ESC key
              *cancelled = 1;
              break;
          } else if (ch == KEY_BACKSPACE || ch == 127 || ch == '\b') {
              if (!input.empty()) {
                  input.pop_back();
                  int len = input.size();
                  mvwprintw(bar, 0, len + 1, " ");
                  wmove(bar, 0, len + 1);
                  wrefresh(bar);
              }
          } else if (input.size() < MAX_INPUT - 1 && ch >= 32 && ch <= 126) {
              input.push_back(ch);
              mvwprintw(bar, 0, input.size(), "%c", ch);
              wrefresh(bar);
          }
      }
  
      noecho();
      curs_set(0);
      werase(bar);
      wrefresh(bar);
  
      if (*cancelled) {
          return "";
      }
  
      return input;
  }
  };
  
class Actions {
private: 
public:  
};

class KeyPressHandler {
  private:
  public:
};


int main(int argc, char *argv[]) {
  if (argc > 1) {
    ArgvType argType = classifyArgv(argv[1]);
    if (argType == ARG_VERSION) {
      std::cout << "te version " << VERSION << std::endl;
      return 0;
    } else if (argType == ARG_HELP) {
      std::cout << "Usage: te [options] [file/folder]\n"
                << "Options:\n"
                << "  --version   Show version information\n"
                << "  --help      Show this help message\n"
                << "  --config    Show configuration options\n";
      return 0;
    } else if (argType == ARG_CONFIG) {
      std::cout << "Configuration options are not implemented yet.\n";
      return 0;
    }
  }

  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(1);

  int ch;
  while ((ch = getch()) != 'q') {
    
  }

  endwin();
  return EXIT_SUCCESS;
}
