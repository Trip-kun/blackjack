#pragma once
#include <ft2build.h>
#include <filesystem>
#include FT_FREETYPE_H
#include <iostream>

#include "GL/Font.hpp"


namespace Fonts {
    FT_Library library;
    Font* roboto;
    Font* loadFont(const char* file);
    void init() {
        if(FT_Init_FreeType(&library)) {
            std::cout << "Could not init freetype library" << std::endl;
            throw "FREETYPE INIT ERROR";
        }
         roboto = loadFont("Roboto-Medium.ttf");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    Font* loadFont(const char* file) {
FT_Face face;
        if(FT_New_Face(library, file, 0, &face)) {
            std::cout << "Could not load font" << std::endl;
            throw "FREETYPE FONT LOAD ERROR";
        }
        Font* f = new Font(face, 72);
        FT_Done_Face(face);
        return f;
    }
    void clean() {
        delete roboto;
        FT_Done_FreeType(library);
    }
}