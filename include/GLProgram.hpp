#pragma once
#include <Shader.hpp>
#include <GL/glew.h>
#include "Context.hpp"
class GLProgram {
public:
  GLProgram (Shader **shader, int size);
  explicit GLProgram(Shader *shader);
  GLProgram (Shader *shader1, Shader *shader2);
  void use(Context* ctx);
  unsigned int getUniformLocation(const char*);
private:
  unsigned int program;
};