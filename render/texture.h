#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <GL/glew.h>

#include <GL/gl.h>

class Texture
{
public:
  Texture()
      : width(0), height(0), id(0), data(nullptr),
        nc_channels(0), mipmaps(false), format(0),
        type(0), filter(GL_UNSIGNED_BYTE), target(GL_TEXTURE_2D) {}
  ~Texture() {}

  int width, height;

  unsigned int id;

  // load a texture from specified path
  void loadFromFile(const char *path, bool mipmaps = false,
                    uint format = GL_RGBA, uint type = GL_UNSIGNED_BYTE);
  // load an empty texture for later use eg post proccessing effects with
  // framebuffers
  void loadEmptyTexture(int w, int h, GLenum target, bool mipmaps = false,
                        uint format = GL_RGBA, uint type = GL_UNSIGNED_BYTE,
                        int filter = GL_LINEAR);

  void loadTexture2DFromRawData(int w, int h, void *data, bool mipmaps = false,
                                uint format = GL_RGBA, int filter = GL_LINEAR,
                                uint type = GL_UNSIGNED_BYTE);
  // create bit map
  void createCharBitmap(int w, int h, void *data);

  inline void clean() const { glDeleteTextures(1, &this->id); }

  inline void freeData() const { free(this->data); }

private:
  void *data;
  int nc_channels;
  bool mipmaps;
  unsigned int format;
  unsigned int type;
  int filter;
  GLenum target;
  // create actual texture
  void create();
};

#endif
