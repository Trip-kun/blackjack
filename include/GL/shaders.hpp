#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "GLProgram.hpp"

namespace Shaders {
    const char * basicVertex = {
        #include "GL/basic.vs"
    };
    const char * basicFragment={
        #include "GL/basic.fs"
    };
    const char *textureVertex = {
        #include "GL/texture.vs"
    };
    const char *textureFragment = {
        #include "GL/texture.fs"
    };
    const char *textVertex = {
        #include "GL/text.vs"
    };
    const char *textFragment = {
        #include "GL/text.fs"
    };
    Shader* basicV;
    Shader* basicF;
    Shader* textureV;
    Shader* textureF;
    Shader* textV;
    Shader* textF;
    GLProgram* basic;
    GLProgram* texture;
    GLProgram* text;
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);;
    void inline load(Context* ctx) {
        textureV= new Shader(textureVertex, GL_VERTEX_SHADER);
        textureF = new Shader(textureFragment, GL_FRAGMENT_SHADER);
        textV = new Shader(textVertex, GL_VERTEX_SHADER);
        textF = new Shader(textFragment, GL_FRAGMENT_SHADER);
        basicV = new Shader(basicVertex, GL_VERTEX_SHADER);
        basicF = new Shader(basicFragment, GL_FRAGMENT_SHADER);
        texture = new GLProgram(textureV, textureF);
        text = new GLProgram(textV, textF);
        basic = new GLProgram(basicV, basicF);
        text->use(ctx);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(text->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }
    void inline clean(Context* ctx) {
        delete basicV;
        delete basicF;
        delete textureV;
        delete textureF;
        delete textV;
        delete textF;
        delete basic;
        delete texture;
        delete text;
    }
}
