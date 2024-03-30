#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include "GL/GLProgram.hpp"
#include <string>
#include "Drawable.hpp"
#include "Font.hpp"
#include "GL/Transforms.hpp"
class Text : Drawable {
public:
    Text(GLProgram* program, Font* font,  const char* text, double x, double y, double scale, Color color);
    void Draw(Context* ctx) override;
    void setOffset(double x, double y);
    void setText(const char* text);
    void setColor(Color color);
    void setScale(double scale);
    static void setHeight(unsigned int);
    static void setWidth(unsigned int);
    ~Text() override;
private:
    static unsigned int VAO, VBO;
    static bool initialized;
    static unsigned int width;
    static unsigned int height;
    GLProgram* program;
    std::string text;
    double x, y;
    Color color;
    double scale;
    Font* font;
};

