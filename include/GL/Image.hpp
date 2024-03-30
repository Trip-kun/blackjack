#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Drawable.hpp"
#include "Texture.hpp"
#include "GLProgram.hpp"
class Image : public Drawable{
public:
    Image(Texture*, GLProgram*, float x, float y, float w, float h, float r=1, float g=1, float b=1);
    ~Image() override;
    void Draw(Context*) override;
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
    Texture* texture;
    GLProgram* program;
    unsigned int* indices;
    float* vertices;
    unsigned int VBO, VAO, EBO;
protected:
    glm::mat4 trans;
};