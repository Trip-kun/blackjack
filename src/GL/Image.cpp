#include "GL/Image.hpp"

Image::Image(Texture* texture, GLProgram* program, Position pos, Color color ) {
    this->texture=texture;
    this->program=program;
    this->x=pos.x;
    this->y=pos.y;
    unsigned int* iS = new unsigned int[]{
        0, 1, 3,
        1, 2, 3
        };
    double* vS = new double[]{
        pos.x+pos.width, pos.y+pos.height, color.r, color.g, color.b, 1.0, 1.0,
        pos.x+pos.width, pos.y, color.r, color.g, color.b, 1.0, 0.0,
        pos.x, pos.y, color.r, color.g, color.b, 0.0, 0.0,
        pos.x, pos.y+pos.height, color.r, color.g, color.b, 0.0, 1.0
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
    glBufferData(GL_ARRAY_BUFFER, 28*sizeof(double), this->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), this->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void*)(2*sizeof(double)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 7 * sizeof(double), (void*) (5*sizeof(double)));
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Image::setOffset(double x, double y) {
    this->x = x;
    this->y = y;
    this->resetTrans();
}
void Image::setTransform(Transform transform) {
    this->transform = transform;
    this->resetTrans();
}
void Image::setTexture(Texture *texture) {
    this->texture=texture;
}

void Image::resetTrans() {
    this->trans = glm::mat4(1.0f);
    this->trans = glm::translate(trans, glm::vec3(this->x-this->pos.x, this->y-this->pos.y, 0));
    this->trans = glm::rotate(trans, (float) glm::radians(this->transform.r), glm::vec3(0.0, 0.0, 1.0));
    this->trans = glm::scale(trans, glm::vec3(this->transform.sx, this->transform.sy, 1));
}