#include "GL/Image.hpp"

#include <iostream>

Image::Image(Texture* texture, GLProgram* program, float x, float y, float w, float h, float r, float g, float b) {
    this->texture=texture;
    this->program=program;
    this->ox=x;
    this->oy=y;
    this->x=x;
    this->y=y;
    unsigned int* iS = new unsigned int[]{
        0, 1, 3,
        1, 2, 3
        };
    float* vS = new float[]{
        x+w, y+h, r, g, b, 1.0, 1.0,
        x+w, y, r, g, b, 1.0, 0.0,
        x, y, r, g, b, 0.0, 0.0,
        x, y+h, r, g, b, 0.0, 1.0
        };
    this->vertices=vS;
    this->indices=iS;
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    this->VBO = VBO;
    this->VAO = VAO;
    this->EBO=EBO;
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, 28*sizeof(float), this->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(int), this->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*) (5*sizeof(float)));
    glEnableVertexAttribArray(2);
    this->trans = glm::mat4(1.0f);
}
Image::~Image() {
    delete[] this->indices;
    delete[] this->vertices;
}
void Image::Draw(Context* ctx) {
    texture->bind();
    program->use(ctx);
    glCullFace(GL_FRONT);
    unsigned int transformLoc = program->getUniformLocation("transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Image::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->resetTrans();
}
void Image::setRotation(float r) {
    this->r = r;
    this->resetTrans();
}
void Image::setScale(float sx, float sy) {
    this->sx = sx;
    this->sy = sy;
    this->resetTrans();
}
void Image::setTexture(Texture *texture) {
    this->texture=texture;
}

void Image::resetTrans() {
    this->trans = glm::mat4(1.0f);
    this->trans = glm::translate(trans, glm::vec3(this->x-this->ox, this->y-this->oy, 0));
    this->trans = glm::rotate(trans, glm::radians(this->r), glm::vec3(0.0, 0.0, 1.0));
    this->trans = glm::scale(trans, glm::vec3(this->sx, this->sy, 1));
}