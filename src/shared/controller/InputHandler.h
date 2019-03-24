#include "Controller.h"
#include "../../config/config.h"
#include "../direct/IO.h"
#include "../direct/Direct.h"

class InputHandler {
public:
  Controller controller;
  int counter;
  void processTilt();
  void init();
  void process();
  Direct input;
};
