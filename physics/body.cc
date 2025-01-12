#include "body.h"
#include "../render/mesh.h"
#include "../render/texture.h"
#include "shape.h"
#include "shapes.h"

Body::Body()
    : draw(true), texture(nullptr), transform(Transform()),
      velocity(Vector3f(0.0)), angularVelocity(Vector3f(0.0)),
      inverseMass(0.0), elasticity(0.5), shape(nullptr),
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
void Body::applyImpulseAngular(const Vector3f &impulse)
{

  if (this->inverseMass == 0.0)
    return;

  // L = I w = r x p
  // dL = I dw = r x J
  // => dw = I ^−1 * ( r x J )

  this->angularVelocity += this->getInertiaTensorWorldSpace() * impulse;
  const float maxAngularSpeed = 30.0f;
  if (this->angularVelocity.magSqrd() > maxAngularSpeed * maxAngularSpeed)
  {
    this->angularVelocity = this->angularVelocity.unit();
    this->angularVelocity *= maxAngularSpeed;
  }
}
void Body::applyImpulse(const Vector3f &pointImpulse, const Vector3f &impulse)
{
  if (this->inverseMass == 0.0)
    return;

  this->applyimpulseLinear(impulse);

  Vector3f position = this->getCenterOfMassWorldSpace();

  Vector3f r = pointImpulse - position;
  Vector3f dl = cross(r, impulse);
  this->applyImpulseAngular(dl);
}

Vector3f Body::getCenterOfMassWorldSpace() const
{
  const Vector3f pos = this->pos();
  const Quat rotation = this->orientation();
  const Vector3f centerOfMass = this->shape->getCenterOfMass();
  return pos + rotation * centerOfMass;
}
Vector3f Body::getCenterOfMassModelSpace() const
{
  return this->shape->getCenterOfMass();
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

  invInertiaTensor = orient * invInertiaTensor * orient.transpose();
  return invInertiaTensor;
}

void Body::update(const float dt)
{
  this->translate(this->pos() + this->velocity * dt);

  Vector3f positionCm = this->getCenterOfMassWorldSpace();
  Vector3f cmToPos = this->pos() - positionCm;
  // T = T_external + omega x I * omega
  // T = I a = w x I * w
  // a = I ^−1 ( w x I * w )
  Mat3x3 orientation = this->orientation().toMat3x3();
  Mat3x3 intertiaTensor = orientation * this->shape->inertiaTensor() * orientation.transpose();
  Vector3f alpha = intertiaTensor.inverse() * cross(this->angularVelocity, intertiaTensor * this->angularVelocity);
  this->angularVelocity += alpha * dt;

  Vector3f dAngle = this->angularVelocity * dt;
  Quat dq = Quat(dAngle.mag(), dAngle);
  this->orient(dq * this->orientation());
  this->orient(this->orientation().unit());

  this->translate(positionCm + dq * cmToPos);
}