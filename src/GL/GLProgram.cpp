#include "GL/GLProgram.hpp"
GLProgram::GLProgram(Shader* shader) {
  this->program = glCreateProgram();
  glAttachShader(this->program, shader->shader);
  glLinkProgram(this->program);
}

GLProgram::GLProgram(Shader** shaders, int size) {
  this->program = glCreateProgram();
  for (int i = 0; i<size; i++) {
    glAttachShader(this->program, shaders[i]->shader);
  }
  glLinkProgram(this->program);
}

GLProgram::GLProgram(Shader* shader1, Shader* shader2) {
  this->program = glCreateProgram();
  glAttachShader(this->program, shader1->shader);
  glAttachShader(this->program, shader2->shader);
  glLinkProgram(this->program);
}

void GLProgram::use(Context* ctx) {
  ctx->useProgram(this->program);
  glUseProgram(this->program);

}

unsigned int GLProgram::getUniformLocation(const char * uniform) {
  return glGetUniformLocation(this->program, uniform);
}
