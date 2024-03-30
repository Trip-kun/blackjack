#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Drawable.hpp"
#include "Texture.hpp"
#include "GLProgram.hpp"
#include "GL/Transforms.hpp"
class Image : public Drawable{
public:
    Image(Texture*, GLProgram*, Position pos, Color color = {1, 1, 1});
    ~Image() override;
    void Draw(Context*) override;
    void setOffset(double x, double y);
    void setTransform(Transform transform);
    void setTexture(Texture* texture);
private:
    Position pos;
    Transform transform;
    double x, y;
    void resetTrans();
    Texture* texture;
    GLProgram* program;
    unsigned int* indices;
    double* vertices;
    unsigned int VBO, VAO, EBO;
protected:
    glm::mat4 trans;
};