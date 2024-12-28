#include "../headers/assets.h"
#include "../shapes/cube.h"
#include "../shapes/shape.h"
#include "../shapes/sphere.h"
// #include "../shapes/torus.h"

void AssetManager::addSphere(std::string name, float radius, int longs,
                             int lats, color3f col) {
  bool addObject = true;

  for (auto &shape : shapes) {
    if (shape.first == name) {
      std::cout << "object already exits! please change name." << std::endl;
      addObject = false;
      break;
    }
  }
  if (addObject) {
    shapes.insert(std::make_pair(name, new Sphere(radius, longs, lats, col)));
  }
}

void AssetManager::addCube(std::string name, color3f col, v3D size) {
  bool addObject = true;

  for (auto &shape : shapes) {
    if (shape.first == name) {
      std::cout << "object already exits! please change name." << std::endl;
      addObject = false;
      break;
    }
  }
  if (addObject) {
    shapes.insert(std::make_pair(name, new Cube(col, size)));
  }
}
/*void AssetManager::addTorus(std::string name, int divs, color3f col) {
  bool addObject = true;

  for (auto &shape : shapes) {
    if (shape.first == name) {
      std::cout << "object already exits! please change name." << std::endl;
      addObject = false;
      break;
    }
  }
  if (addObject) {
    shapes.insert(std::make_pair(name, new Torus(divs, col)));
  }
}*/

void AssetManager::refreshShapeList() {
  int counter = 0;
  objectListSize = getTotalShapes();
  for (auto &shape : shapes) {
    objectList[counter] = shape.first.c_str();
    counter++;
  }
}
void AssetManager::removeShape(std::string name) {
  bool objectRemoved = false;

  for (auto &shape : shapes) {
    if (shape.first == name) {
      shapes.erase(name);
      std::cout << "object removed successfully." << std::endl;
      objectRemoved = true;
    }
  }
  if (!objectRemoved) {
    std::cout << "object not found and removed!" << std::endl;
  }
}
Shape *AssetManager::getShape(std::string name) {
  bool objectExists = false;
  std::string objName = "";
  for (auto &shape : shapes) {
    if (shape.first == name) {
      objName = name;
      objectExists = true;
      break;
    }
  }
  if (!objectExists) {
    std::cout << "object does not exist!" << std::endl;
  }
  return shapes.at(objName);
}
void AssetManager::listShapes() {
  std::cout << "number of available objects: " << shapes.size() << std::endl;
  std::cout << "list of objects:" << std::endl;

  for (auto &shape : shapes) {
    std::cout << shape.first << "." << std::endl;
  }
}

int AssetManager::getVertCount() {
  int count = 0;
  for (auto &shape : shapes) {
    // count += shape.second->vertCout();
  }

  return count;
}

void AssetManager::cleanUp() {
  for (auto &shape : shapes) {
    shape.second->clean();
    delete shape.second;
  }
  shapes.clear();
}
