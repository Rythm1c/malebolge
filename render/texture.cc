
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "texture.h"
#include "stb_image.h"

void Texture::loadFromFile(
    const char *path, bool _mipmaps, uint _format,
    uint _type)
{
  this->target = GL_TEXTURE_2D;
  this->filter = GL_LINEAR;

  this->data = stbi_load(path, &this->width, &this->height, &this->nc_channels, 0);
  if (this->data == nullptr)
  {
    std::cout << "failed to load texture" << std::endl;
  }
  if (this->nc_channels != 4)
  {
    this->format = GL_RGB;
  }
  this->mipmaps = _mipmaps;
  this->format = _format;
  this->type = _type;
  create();

  stbi_image_free(this->data);
}
void Texture::loadEmptyTexture(
    int w, int h, GLenum _target, bool _mipmaps,
    uint _format, uint _type, int _filter)
{
  this->width = w;
  this->height = h;
  this->target = _target;
  this->mipmaps = _mipmaps;
  this->format = _format;
  this->type = _type;
  this->filter = _filter;

  create();
}
void Texture::loadTexture2DFromRawData(
    int w, int h, void *_data, bool _mipmaps,
    uint _format, uint _type, int _filter)
{
  this->width = w;
  this->height = h;
  this->target = GL_TEXTURE_2D;
  this->mipmaps = _mipmaps;
  this->format = _format;
  this->type = _type;
  this->filter = _filter;
  this->data = _data;

  this->create();
}

void Texture::createCharBitmap(int w, int h, void *data)
{
  // character rendering settings
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(1, &this->id);
  glBindTexture(GL_TEXTURE_2D, this->id);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE,
               data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::create()
{
  glGenTextures(1, &this->id);
  glBindTexture(this->target, this->id);

  glTexImage2D(this->target, 0, this->format, this->width, this->height, 0, this->format, this->type, this->data);

  if (this->mipmaps)
  {
    glGenerateMipmap(this->target);
    glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }
  else
  {
    glTexParameteri(this->target, GL_TEXTURE_MIN_FILTER, this->filter);
  }
  glTexParameteri(this->target, GL_TEXTURE_MAG_FILTER, this->filter);
  glTexParameteri(this->target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(this->target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(this->target, 0);
}
