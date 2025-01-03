#include "shape.h"
#include "../render/mesh.h"

void Shape::applyimpulseLinear(const Vector3f &impulse)
{
  if (this->inverseMass == 0.0)
    return;
  // p = mv
  // dp = m dv = j
  //=> dv = j / m
  this->velocity += impulse * this->inverseMass;
}
void Shape::init() { mesh->init(); }
void Shape::render() { mesh->render(); }
void Shape::clean() { mesh->clean(); }
