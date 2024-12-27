#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>

#include <GL/glew.h>

#include <GL/gl.h>

class Texture {
public:
  Texture() {}
  ~Texture() {}

  int _width, _height;

  unsigned int _texture;

  // load a texture from specified path
  void load_from_file(const char *path, bool mipmaps = false,
                      uint format = GL_RGBA, uint type = GL_UNSIGNED_BYTE);
  // load an empty texture for later use eg post proccesssing effects with
  // framebuffers
  void load_empty_texture(int w, int h, GLenum target, bool mipmaps = false,
                          uint format = GL_RGBA, uint type = GL_UNSIGNED_BYTE,
                          int filter = GL_LINEAR);
  // create bit map
  void create_char_bitmap(int w, int h, void *data);

  void clean() { glDeleteTextures(1, &_texture); }

private:
  void *_data = nullptr;
  int _nc_channels;
  bool _mipmaps;
  unsigned int _format;
  unsigned int _type;
  int _filter;
  GLenum _target;
  // create actual texture
  void create();
};

#endif
