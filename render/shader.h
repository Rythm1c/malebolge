#ifndef SHADER
#define SHADER

#include "../math/mat4.h"
#include "../math/vec3.h"

class Shader {
public:
  Shader() {}
  ~Shader() {}
  Shader(const char *vert_path, const char *frag_path);

  unsigned int program;

  void use();
  void clean();
  void load(const char *vert_path, const char *frag_path);

  void updateInt(const char *name, int value);
  void updateFloat(const char *name, float value);
  void updateVec3(const char *name, const Vector3f &vec);
  void updateMat4(const char *name, const Mat4x4 &mat);

private:
};
#endif
