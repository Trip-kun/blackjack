#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include "GL/GLProgram.hpp"
#include "GL/Context.hpp"
#include "GL/Transforms.hpp"
#include "GL/Drawable.hpp"

class Hexic : public Drawable {
public:
    Hexic(GLProgram* program, Position pos, Color color = {1, 1, 1});
    ~Hexic() override;
    void Draw(Context* ctx) override;
    void setOffset(double x, double y);
    void setTransform(Transform transform);
private:
    Position pos;
    Transform transform;
    Color color;
    double x, y;
    void resetTrans();
    GLProgram* program;
    int* indices;
    double* vertices1;
    double* vertices2;
    unsigned int VBO1, VAO1, EBO1;
    unsigned int VBO2, VAO2, EBO2;
    int* triangulate(int nPoints, int* out);
    void setVertices(int a1, int b1, int c1, double* vertices, int& count, double xMul, double yMul);
    void setVertices2(int a1, int b1, int c1, double *vertices, int& count, double xMul, double yMul);
    glm::mat4 trans;
};