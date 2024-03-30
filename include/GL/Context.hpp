#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
class Context {
private:
    unsigned int activeProgram;
    void useProgram(unsigned int program);
public:
    friend class GLProgram;
};
