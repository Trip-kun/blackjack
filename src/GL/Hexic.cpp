#include "GL/Hexic.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.inl>

Hexic::Hexic(GLProgram *program, Position pos, Color color) {
    this->program=program;
    this->pos=pos;
    this->color=color;
    int count = 0;
    double* vS = new double[5*160]; // 160 elements at this precision
    setVertices(0, 40, 1, vS, count, 1.0, 1.0);
    setVertices(40.0, 0.0, -1, vS, count, 1.0, -1.0);
    setVertices(0.0, 40.0, 1, vS, count, -1.0, -1.0);
    setVertices(40.0, 0.0, -1, vS, count, -1.0, 1.0);
    count=0;
    double* vS2 = new double[5*160]; // 160 elements at this precision
    setVertices2(0.0, 40.0, 1, vS2, count, 1.0, 1.0);

    setVertices2(40.0, 0.0, -1, vS2, count, 1.0, -1.0);
    setVertices2(0.0, 40.0, 1, vS2, count, -1.0, -1.0);
    setVertices2(40.0, 0.0, -1, vS2, count, -1.0, 1.0);

    this->indices=triangulate(160, this->indices);
    this->vertices1 = vS;
    this->vertices2 = vS2;
    //*/
    unsigned int VBO1, VAO1, EBO1;

    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO1);
    this->VBO1 = VBO1;
    this->VAO1 = VAO1;
    this->EBO1=EBO1;
    glBindVertexArray(this->VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO1);
    glBufferData(GL_ARRAY_BUFFER, 5*160*sizeof(double), this->vertices1, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*158*sizeof(unsigned int), this->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2*sizeof(double)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    unsigned int VBO2, VAO2, EBO2;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    this->VBO2 = VBO2;
    this->VAO2 = VAO2;
    this->EBO2=EBO2;
    glBindVertexArray(this->VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO2);
    glBufferData(GL_ARRAY_BUFFER, 5*160*sizeof(double), this->vertices2, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*158*sizeof(unsigned int), this->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2*sizeof(double)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    this->trans = glm::mat4(1.0f);
    //*/
}
void Hexic::setVertices(int a1, int b1, int c1, double *vertices, int& count, double xMul, double yMul) {
    for (int i2=a1; b1<a1 ? i2>b1 : i2<b1; i2+=c1) {
        double i = i2/40.0;
        vertices[5*(count)] = (xMul*pos.width/2)*pow(i, 1.0/8.0)+(pos.width/2.0)+pos.x;
        double a = i*pow(pos.width/2, 8);
        double b = a/pow(pos.width/2, 8);
        double c = (1-b)*(pow(pos.height/2, 8));
        double d = pow(c, 1.0/8.0);
        vertices[5*(count)+1] = (yMul*d)+pos.height/2+pos.y;
        vertices[(5*count)+2] = color.r;
        vertices[(5*count)+3] = color.g;
        vertices[5*(count)+4] = color.b;
        count++;
    }
}
void Hexic::setVertices2(int a1, int b1, int c1, double *vertices, int& count, double xMul, double yMul) {
    for (int i2=a1; b1<a1 ? i2>b1 : i2<b1; i2+=c1) {
        double i = i2/40.0;
        double h = pos.height/2*0.1;
        vertices[5*(count)] = xMul*(pos.width/2-h)*pow(i, 1.0/8.0)+pos.width/2+pos.x;
        double a = pow((pos.width/2-h), 8)*i;
        double b = a/pow(pos.width/2-h, 8);
        double c = (1-b)*(pow(h*9, 8));
        double d = pow(c, 1.0/8.0);
        vertices[5*(count)+1] = (yMul*d)+pos.height/2+pos.y;
        vertices[5*(count)+2] = color.r*(154.0/256.0);
        vertices[5*(count)+3] = color.g*(154.0/256.0);
        vertices[5*(count)+4] = color.b*(154.0/256.0);
        count++;
    }
}
Hexic::~Hexic() {
    delete[] this->indices;
    delete[] this->vertices1;
    delete[] this->vertices2;
}
void Hexic::Draw(Context *ctx) {

    program->use(ctx);
    glCullFace(GL_FRONT);
    unsigned int transformLoc = program->getUniformLocation("proj");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindVertexArray(this->VAO1);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO1);
    glDrawElements(GL_TRIANGLES, 3*158, GL_UNSIGNED_INT, 0);

    //*

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO2);
    glBindVertexArray(this->VAO2);
    glDrawElements(GL_TRIANGLES, 3*158, GL_UNSIGNED_INT, 0);

    //*/
}


void Hexic::setOffset(double x, double y) {
    this->x = x;
    this->y = y;
    this->resetTrans();
}
void Hexic::setTransform(Transform transform) {
    this->transform = transform;
    this->resetTrans();
}
void Hexic::resetTrans() {
    this->trans = glm::mat4(1.0f);
    this->trans = glm::translate(trans, glm::vec3(this->x-this->pos.x, this->y-this->pos.y, 0));
    this->trans = glm::rotate(trans, (float) glm::radians(this->transform.r), glm::vec3(0.0, 0.0, 1.0));
    this->trans = glm::scale(trans, glm::vec3(this->transform.sx, this->transform.sy, 1));
}
int* Hexic::triangulate(int nPoints, int* out) {
    out = new int[3*(nPoints-2)];
    for (int i = 2; i < nPoints; i++) {
        out[3*(i-2)] = i-1;
        out[3*(i-2)+1] = i;
        out[3*(i-2)+2] = 0;
    }

    return out;
}