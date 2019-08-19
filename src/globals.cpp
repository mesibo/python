// global.cpp

#include "globals.h"
#include <Python.h>
#include <termios.h>
#include <mesibo.h>

// To build a debug version of mesibo set gDebugEnabled  
int gDebugEnabled = 0;


// Used by mesibo.wait()
int keypress() {
  struct termios old_state, new_state;
  int c;

  tcgetattr(STDIN_FILENO, &old_state);
  new_state = old_state;

  new_state.c_lflag &= ~(ECHO | ICANON);
  new_state.c_cc[VMIN] = 1;

  tcsetattr(STDIN_FILENO, TCSANOW, &new_state);

  c = getchar();

  /* restore the saved state */
  tcsetattr(STDIN_FILENO, TCSANOW, &old_state);
  return c;
}

IMesibo* m_api = NULL;
