#pragma once

#include <iostream>
#include <string>
#include <map>
#include "../math/vec3.h"

class Shape;

class AssetManager
{
public:
    AssetManager() : objectListSize(0), objectList({nullptr}) {}
    ~AssetManager() {}

    void listShapes();
    void addShape(std::string);
    void addSphere(std::string, int, int, color3f);
    void addCube(std::string, color3f);
    void addTorus(std::string, int, color3f);
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