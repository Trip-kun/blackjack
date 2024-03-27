#pragma once
#include "GL/glew.h"
#include "Drawable.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.hpp"
#include "GLProgram.hpp"
class Image {
public:
    Image(Texture*, GLProgram*, float x, float y, float w, float h, float r=1, float g=1, float b=1);
    ~Image();
    void Draw(Context*);
    void setPosition(float x, float y);
    void setRotation(float r);
    void setScale(float sx, float sy);
    void setTexture(Texture* texture);
private:
    float x, y;
    float r=0;
    float sx = 1;
    float sy = 1;
    float ox, oy;
    void resetTrans();
    glm::mat4 trans;
    Texture* texture;
    GLProgram* program;
    unsigned int* indices;
    float* vertices;
    unsigned int VBO, VAO, EBO;
};