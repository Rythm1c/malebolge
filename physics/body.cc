#include "body.h"
#include "../render/mesh.h"
#include "../render/texture.h"
#include "shape.h"
#include "shapes.h"

Body::Body()
    : draw(true), texture(nullptr), transform(Transform()),
      velocity(Vector3f(0.0)), inverseMass(0.0), elasticity(0.5), shape(nullptr),
      mesh(new Mesh()) {};

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

  default:
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

Mat3x3 Body::getInertiaTensorLocalSpace() const
{
  Mat3x3 inertiaTensor = this->shape->inertiaTensor();
  Mat3x3 invInertiaTensor = inertiaTensor.inverse() * this->inverseMass;

  return invInertiaTensor;
}
Mat3x3 Body::getInertiaTensorWorldSpace() const
{
  Mat3x3 inertiaTensor = this->shape->inertiaTensor();
  Mat3x3 invInertiaTensor = inertiaTensor.inverse() * this->inverseMass;
  Mat3x3 orient = this->orientation().toMat3x3();

  inverseTensor = orient * invInertiaTensor * orient.transpose();
  return invInertiaTensor;
}
