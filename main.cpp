#include "headers/engine.h"

Engine *Engine::instancePtr = new Engine();

int main(int argc, char *argv[])
{
  
    try
    {
        Engine::getInstance()->run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}