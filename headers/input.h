#ifndef _INPUT
#define _INPUT

#include "../math/vec2.h"
#include <iostream>

class World;

class InputHandler {
private:
  World *P_world;
  void specialKeys();
  void keyboard(float);

  const unsigned char *keyboardState;

public:
  InputHandler() {}
  ~InputHandler() {}
  InputHandler(World *_w);

  void processInput(float);
  void populateKeys();
};

#endif
