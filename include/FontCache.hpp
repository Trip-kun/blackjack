#pragma once
#include <filesystem>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <iostream>

#include "GL/Font.hpp"

class Fonts {
public:
    Fonts() {
    }
    std::map<unsigned int, Font*>* fonts;
    FT_Library* library;
    void init() {
        library = new FT_Library();
        fonts = new std::map<unsigned int, Font*>();
        if(FT_Init_FreeType(library)) {
            std::cout << "Could not init freetype library" << std::endl;
            throw "FREETYPE INIT ERROR";
        }
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    Font* loadFont(const char* file, unsigned int size) {
        if ((*fonts).find(size) != (*fonts).end()) {

            return (*fonts)[size];
        }
        FT_Face face;
        if(FT_New_Face(*library, file, 0, &face)) {
            std::cout << "Could not load font" << std::endl;
            throw "FREETYPE FONT LOAD ERROR";
        }
        Font* f = new Font(face, size);
        (*fonts)[size] = f;
        FT_Done_Face(face);
        return f;
    }
    Font* getFont(unsigned int size) {
        return loadFont("Roboto-Medium.ttf", size);
    }
    void clean() {
        for (auto& font : *fonts) {
            delete font.second;
        }
        FT_Done_FreeType(*library);
        delete library;
        delete fonts;
    }
};