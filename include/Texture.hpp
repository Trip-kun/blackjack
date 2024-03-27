#pragma once
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
class Texture {
private:
    unsigned int texture;
    int width;
    int height;
    int channels;
    unsigned char* data;
public:
    Texture(const char* filename);
    void releaseImage();
    void bind();
    friend class Drawable;
    friend int main();
};