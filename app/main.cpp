#include "../core/te.cpp"


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
  } else {
    std::cout << "Menu screen is not implemented yet :( \n\nPlease give a file or folder name as argv" << std::endl;
    return EXIT_FAILURE;
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
