#include "GL/Text.hpp"

#include <glm/gtc/type_ptr.hpp>
unsigned int Text::VAO, Text::VBO;
bool Text::initialized = false;
Text::Text(GLProgram* program, Font* font, const char* text, float x, float y, float scale, float r, float g, float b) {
    if (!initialized) {
        initialized = true;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    this->program = program;
    this->font = font;
    this->text = text;
    this->x = x;
    this->y = y;
    this->scale = scale;
    this->r = r;
    this->g = g;
    this->b = b;
    this->text = std::string(text);
}
void Text::Draw(Context* ctx) {
    program->use(ctx);
    glCullFace(GL_BACK);
    float x_ = x;
    glUniform3f(program->getUniformLocation("textColor"), r, g, b);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Font::Character* ch1 = font->getCharacter(*c);
        
        float xpos = x_ + ch1->Bearing.x * scale;
        float ypos = y - (ch1->Size.y - ch1->Bearing.y) * scale;

        float w = ch1->Size.x * scale;
        float h = ch1->Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch1->TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x_ += (ch1->Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
void Text::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
}
void Text::setText(const char* text) {
    this->text = std::string(text);
}
void Text::setColor(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}
void Text::setScale(float scale) {
    this->scale = scale;
}
Text::~Text() {
}