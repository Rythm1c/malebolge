#include "../headers/texture.h"
#include "../headers/stb_image.h"

void Texture::load_from_file(const char *path, bool mipmaps, uint format,
                             uint type) {
  _target = GL_TEXTURE_2D;
  _filter = GL_LINEAR;

  _data = stbi_load(path, &_width, &_height, &_nc_channels, 0);
  if (_data == nullptr) {
    std::cout << "failed to load texture" << std::endl;
  }
  if (_nc_channels != 4) {
    _format = GL_RGB;
  }
  _mipmaps = mipmaps;
  _format = format;
  _type = type;
  create();

  stbi_image_free(_data);
}
void Texture::load_empty_texture(int w, int h, GLenum target, bool mipmaps,
                                 uint format, uint type, int filter) {
  _width = w;
  _height = h;
  _target = target;
  _mipmaps = mipmaps;
  _format = format;
  _type = type;
  _filter = filter;

  create();
}

void Texture::create_char_bitmap(int w, int h, void *data) {
  // character rendering settings
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE,
               data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::create() {
  glGenTextures(1, &_texture);
  glBindTexture(_target, _texture);

  glTexImage2D(_target, 0, _format, _width, _height, 0, _format, _type, _data);

  if (_mipmaps) {
    glGenerateMipmap(_target);
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  } else {
    glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, _filter);
  }
  glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, _filter);
  glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(_target, 0);
}
