#include "../headers/model.h"
#include "../headers/mesh.h"
#include "../math/transform.h"

Model::Model() : transform(new Transform()), color(color3f(1.0)) {}

void Model::translate(v3D pos) { this->transform->translation = pos; }

void Model::scale(v3D size) { this->transform->scaling = size; }

void Model::orient(Quat orientation) {
  this->transform->orientation = orientation;
}

mat4x4 Model::get_transform() { return this->transform->get(); }

void Model::init() {
  for (auto &mesh : meshes) {
    mesh.prepareRenderResources();
  }
}

void Model::render() {
  for (auto &mesh : meshes) {
    mesh.render();
  }
}
void Model::clean() {
  delete transform;

  for (auto &mesh : meshes) {
    mesh.clean();
  }
}
