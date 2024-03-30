#pragma once
#include <iostream>
#include <map>
#include <GLFW/glfw3.h>

#include "GL/Image.hpp"
#include "GUI/Element.hpp"
template <typename T> class ImageButton : public Image, public Element<T> {
    static double dotProduct(glm::vec2 U, glm::vec2 V) {
        return U.x*V.x + U.y*V.y;
    }
    static glm::vec2 getVector(glm::vec4 A, glm::vec4 B) {
        return {B.x-A.x, B.y-A.y};
    }
public:
    ImageButton(Texture *texture, GLProgram *program, float x, float y, float width, float height, float r, float g, float b) : Image(texture, program, x, y, width, height, r, g, b) {
        this->lastClick=0;
        this->lastRelease=0;
        this->x=x;
        this->y=y;
        this->width=width;
        this->height=height;
    }
    void Click(double button, double x, double y, T t) override {
        glm::vec4 click = glm::vec4(x, y, 0, 1);
        glm::vec4 P = this->trans*click;
        glm::vec4 bottomLeft = glm::vec4(this->x, this->y, 0, 1);
        glm::vec4 bottomRight = glm::vec4(this->x+this->width, this->y, 0, 1);
        glm::vec4 topRight = glm::vec4(this->x+this->width, this->y+this->height, 0, 1);
        glm::vec4 A = this->trans*bottomLeft;
        glm::vec4 B = this->trans*bottomRight;
        glm::vec4 C = this->trans*topRight;
        glm::vec2 AB = getVector(A, B);
        glm::vec2 AP = getVector(A, P);
        glm::vec2 BC = getVector(B, C);
        glm::vec2 BP = getVector(B, P);
        double dotABAP = dotProduct(AB, AP);
        double dotABAB = dotProduct(AB, AB);
        double dotBCBP = dotProduct(BC, BP);
        double dotBCBC = dotProduct(BC, BC);
        if (0 <= dotABAP && dotABAP <= dotABAB && 0 <= dotBCBP && dotBCBP <= dotBCBC && button==GLFW_MOUSE_BUTTON_LEFT) {
            for (auto const& onClick : this->onClicks) {
                onClick.second(t);
            }
        }
    }
    void Release(double button, double x, double y, T t) override {
        glm::vec4 click = glm::vec4(x, y, 0, 1);
        glm::vec4 P = this->trans*click;
        glm::vec4 bottomLeft = glm::vec4(this->x, this->y, 0, 1);
        glm::vec4 bottomRight = glm::vec4(this->x+this->width, this->y, 0, 1);
        glm::vec4 topRight = glm::vec4(this->x+this->width, this->y+this->height, 0, 1);
        glm::vec4 A = this->trans*bottomLeft;
        glm::vec4 B = this->trans*bottomRight;
        glm::vec4 C = this->trans*topRight;
        glm::vec2 AB = getVector(A, B);
        glm::vec2 AP = getVector(A, P);
        glm::vec2 BC = getVector(B, C);
        glm::vec2 BP = getVector(B, P);
        double dotABAP = dotProduct(AB, AP);
        double dotABAB = dotProduct(AB, AB);
        double dotBCBP = dotProduct(BC, BP);
        double dotBCBC = dotProduct(BC, BC);
        if (0 <= dotABAP && dotABAP <= dotABAB && 0 <= dotBCBP && dotBCBP <= dotBCBC && button==GLFW_MOUSE_BUTTON_LEFT) {
            for (auto const& onRelease : this->onReleases) {
                onRelease.second(t);
            }
        }
    }
    unsigned int onClick(void (*func)(T)) {
        this->onClicks[this->lastClick] = func;
        return this->lastClick++;
    }
    unsigned int onRelease(void (*func)(T)) {
        this->onReleases[this->lastRelease] = func;
        return this->lastRelease++;
    }
    void removeOnClick(int id) {
        this->onClicks.erase(id);
    }
    void removeOnRelease(int id) {
        this->onReleases.erase(id);
    }
private:
    float x, y, width, height;
    std::map<unsigned int, void (*)(T)> onClicks;
    std::map<unsigned int, void (*)(T)> onReleases;
    unsigned int lastClick, lastRelease;;

};