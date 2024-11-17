#include "../headers/model.h"
#include "../headers/mesh.h"
#include "../math/transform.h"

Model::Model() : transform(new Transform()), color(color3f(1.0)) {}

void Model::init()
{
    for (auto &mesh : meshes)
    {
        mesh.prepareRenderResources();
    }
}

void Model::render()
{
    for (auto &mesh : meshes)
    {
        mesh.render();
    }
}
void Model::clean()
{
    delete transform;

    for (auto &mesh : meshes)
    {
        mesh.clean();
    }
}
