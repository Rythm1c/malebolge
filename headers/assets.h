#pragma once

#include "../math/vec3.h"
#include <iostream>
#include <map>
#include <string>

class Shape;

class AssetManager {
public:
  AssetManager() : objectListSize(0) {}
  ~AssetManager() {}

  void listShapes();
  void addSphere(std::string, float, int, int, Color3f);
  void addCube(std::string, Color3f, Vector3f);
  void addTorus(std::string, int, Color3f);
  void removeShape(std::string);
  Shape *getShape(std::string);

  inline int getTotalShapes() { return shapes.size(); }

  void refreshShapeList();

  const char *objectList[500];
  int objectListSize;

  int getVertCount();
  void cleanUp();

  // std::map<std::string, Object *> objects;
  std::map<std::string, Shape *> shapes;
};
