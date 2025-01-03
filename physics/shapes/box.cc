#include "box.h"
Box::Box(Vector3f size)
{

  this->transform.scaling = size;
  this->dimensions = size;
}

BoundingBox Box::getBounds() const
{
  return BoundingBox{
      .min = this->transform.translation - this->dimensions,
      .max = this->transform.translation + this->dimensions,
  };
}
