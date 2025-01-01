#include "framebuffer.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

void Framebuffer::detach() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
void Framebuffer::use()
{
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);
  glViewport(0, 0, area.x, area.y);
}

void Framebuffer::load()
{
  glCreateFramebuffers(1, &FBO);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO);

  glGenTextures(1, &frame);
  glBindTexture(GL_TEXTURE_2D, frame);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, area.x, area.y, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         frame, 0);

  glGenRenderbuffers(1, &RBO);
  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, area.x, area.y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, RBO);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    std::runtime_error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Framebuffer::reScale()
{

  glBindTexture(GL_TEXTURE_2D, frame);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, area.x, area.y, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         frame, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, RBO);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, area.x, area.y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, RBO);
}
void Framebuffer::updateVertexData(Vector2f p, Vector2f a)
{
  pos = p;
  area = a;

  vertices = {Vector4f(pos.x, pos.y, 0.0, 0.0), Vector4f(pos.x, pos.y + area.y, 0.0, 1.0),
              Vector4f(pos.x + area.x, pos.y + area.y, 1.0, 1.0),
              Vector4f(pos.x + area.x, pos.y, 1.0, 0.0)};

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector4f) * vertices.size(),
                  vertices.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void Framebuffer::loadQuad(Vector2f p, Vector2f a)
{
  pos = p;
  area = a;

  vertices = {Vector4f(pos.x, pos.y, 0.0, 0.0), Vector4f(pos.x, pos.y + area.y, 0.0, 1.0),
              Vector4f(pos.x + area.x, pos.y + area.y, 1.0, 1.0),
              Vector4f(pos.x + area.x, pos.y, 1.0, 0.0)};
  indices = {0, 1, 2, 0, 2, 3};

  glCreateVertexArrays(1, &VAO);
  glCreateBuffers(1, &VBO);
  glCreateBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4f) * vertices.size(), vertices.data(),
               GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(),
               indices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vector4f), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector4f),
                        (void *)(sizeof(Vector2f)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
void Framebuffer::renderIntoQuad()
{
  glBindVertexArray(VAO);
  glBindTexture(GL_TEXTURE_2D, frame);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
void Framebuffer::clean()
{
  glDeleteBuffers(1, &EBO);
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &RBO);
  glDeleteFramebuffers(1, &FBO);
  glDeleteTextures(1, &frame);
}
