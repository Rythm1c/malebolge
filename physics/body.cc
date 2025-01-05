#include "body.h"
#include "../render/mesh.h"
#include "../render/texture.h"
#include "shape.h"
#include "shapes.h"

Body::Body()
    : draw(true), texture(nullptr), transform(Transform()),
      velocity(Vector3f(0.0)), inverseMass(0.0), shape(nullptr), mesh(new Mesh()) {};

void Body::setShape(Shape *_shape)
{
  this->shape = _shape;

  switch (_shape->getType())
  {
  case SHAPE_SPHERE:
    this->transform.scaling = Vector3f(dynamic_cast<Sphere *>(_shape)->getRadius());
    break;
  case SHAPE_CUBE:
    /*  Vector3f dimensions = dynamic_cast<Box *>(_shape)->getDimensions();
     this->transform.scaling = dimensions; */
    break;
  }
}

void Body::applyimpulseLinear(const Vector3f &impulse)
{
  if (this->inverseMass == 0.0)
    return;
  // p = mv
  // dp = m dv = j
  //=> dv = j / m
  this->velocity += impulse * this->inverseMass;
}

void Body::render()
{
  this->mesh->render();
};

void Body::clean()
{
  this->mesh->clean();
  this->texture->clean();
  delete mesh;
  delete texture;
};