#include "Context.hpp"

void Context::useProgram(unsigned int program) {
    if (program!=this->activeProgram) {
        glUseProgram(program);
        this->activeProgram=program;
    }
}