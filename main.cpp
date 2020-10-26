#include <Windows.h>
#include "include/engine.h"

int main() {
  Engine engine;

  engine.initWindow(640, 480);
  engine.mainLoop();

  return 0;
}
