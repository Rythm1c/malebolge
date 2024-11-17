#ifndef _INPUT
#define _INPUT

#include <iostream>
#include "../math/vec2.h"

class World;

class InputHandler
{
private:
    World *P_world;
    void specialKeys();
    void keyboard();

    const unsigned char *keyboardState;

public:
    InputHandler() {}
    ~InputHandler() {}
    InputHandler(World *_w);

    void processInput();
    void populateKeys();
};

#endif