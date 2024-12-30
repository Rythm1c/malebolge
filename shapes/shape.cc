#include "shape.h"
#include "../headers/mesh.h"

void Shape::applyimpulseLinear(const v3D &impulse)
{
  if (this->inverseMass == 0.0)
    return;
  // p = mv
  // dp = m dv = j
  //=> dv = j / m
  this->velocity += impulse * this->inverseMass;
}
void Shape::init() { mesh->prepareRenderResources(); }
void Shape::render() { mesh->render(); }
void Shape::clean() { mesh->clean(); }
