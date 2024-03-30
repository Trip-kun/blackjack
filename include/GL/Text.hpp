#pragma once
#define GLEW_STATIC
#include "GL/GLProgram.hpp"

#include "Drawable.hpp"
#include "Font.hpp"
#include "GL/glew.h"

class Text : Drawable {
public:
    Text(GLProgram* program, Font* font,  const char* text, float x, float y, float scale, float r, float g, float b);
    void Draw(Context* ctx) override;
    void setPosition(float x, float y);
    void setText(const char* text);
    void setColor(float r, float g, float b);
    void setScale(float scale);
    ~Text() override;
private:
    static unsigned int VAO, VBO;
    static bool initialized;
    GLProgram* program;
    std::string text;
    float x, y;
    float r, g, b;
    float scale;
    Font* font;
};

