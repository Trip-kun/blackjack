#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "GL/Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
Shader::Shader(const char* source, GLenum type) {
  this->shader = glCreateShader(type);
  glShaderSource(this->shader, 1, &source, NULL);
  glCompileShader(this->shader);
  glGetShaderiv(this->shader, GL_COMPILE_STATUS, &this->success);
  if (!this->success) {
    glGetShaderInfoLog(this->shader, 512, NULL, infoLog);
  } else {
    infoLog[0]='O';
    infoLog[1]='K';
    infoLog[2]=0;
  }
}
char* Shader::getInfo() {
  return this->infoLog;
}