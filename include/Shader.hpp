#pragma once
#include <string>
#include <GL/glew.h>
class Shader {
public:
  Shader(const char*, GLenum);
  char* getInfo();
  friend class GLProgram;
  friend int main();
private:
  unsigned int shader;
  int success;
  char infoLog[512];
  unsigned int getShader();
};

