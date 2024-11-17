#include "shape.h"
#include "../headers/mesh.h"

void Shape::init()
{

    mesh->prepareRenderResources();
}

void Shape::render()
{

    mesh->render();
}
void Shape::clean()
{

    mesh->clean();
}
