#include "../core/editor.hpp"

int main(int argc, char *argv[])
{
  TE te;
  te.startApp(argc, argv);
  /*
  while (running) {
    Input input = getUserInput();   // tuşları al
    Event event = mapInputToEvent(input); // ESC, CTRL+X vs. ayrıştır
    handleEvent(event);             // cursor hareketi, edit, komut vs.
    render();                       // buffer'ı terminale çiz
  }
  */
}
