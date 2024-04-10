#include "GL/KeyMonitor.hpp"

#include <iostream>
std::map<Key, KeyMonitor*> KeyMonitor::keyMonitors = std::map<Key, KeyMonitor*>();
KeyMonitor::KeyMonitor(Key key) {
    this->key = key;
    this->lastState = false;
    this->thisState = false;
    this->currentFrame = nullptr;
}
KeyMode KeyMonitor::getState(GLFWwindow* window, KeyFrame *frame, Key key) {
    int keyState=0;
    switch (key) {
        case ESCAPE:
            keyState=glfwGetKey(window, GLFW_KEY_ESCAPE);
            break;
        case A:
            keyState=glfwGetKey(window, GLFW_KEY_A);
            break;
        case B:
            keyState=glfwGetKey(window, GLFW_KEY_B);
            break;
        case C:
            keyState=glfwGetKey(window, GLFW_KEY_C);
            break;
        case D:
            keyState=glfwGetKey(window, GLFW_KEY_D);
            break;
        case E:
            keyState=glfwGetKey(window, GLFW_KEY_E);
            break;
        case F:
            keyState=glfwGetKey(window, GLFW_KEY_F);
            break;
        case G:
            keyState=glfwGetKey(window, GLFW_KEY_G);
            break;
        case H:
            keyState=glfwGetKey(window, GLFW_KEY_H);
            break;
        case I:
            keyState=glfwGetKey(window, GLFW_KEY_I);
            break;
        case J:
            keyState=glfwGetKey(window, GLFW_KEY_J);
            break;
        case K:
            keyState=glfwGetKey(window, GLFW_KEY_K);
            break;
        case L:
            keyState=glfwGetKey(window, GLFW_KEY_L);
            break;
        case M:
            keyState=glfwGetKey(window, GLFW_KEY_M);
            break;
        case N:
            keyState=glfwGetKey(window, GLFW_KEY_N);
            break;
        case O:
            keyState=glfwGetKey(window, GLFW_KEY_O);
            break;
        case P:
            keyState=glfwGetKey(window, GLFW_KEY_P);
            break;
        case Q:
            keyState=glfwGetKey(window, GLFW_KEY_Q);
            break;
        case R:
            keyState=glfwGetKey(window, GLFW_KEY_R);
            break;
        case S:
            keyState=glfwGetKey(window, GLFW_KEY_S);
            break;
        case T:
            keyState=glfwGetKey(window, GLFW_KEY_T);
            break;
        case U:
            keyState=glfwGetKey(window, GLFW_KEY_U);
            break;
        case V:
            keyState=glfwGetKey(window, GLFW_KEY_V);
            break;
        case W:
            keyState=glfwGetKey(window, GLFW_KEY_W);
            break;
        case X:
            keyState=glfwGetKey(window, GLFW_KEY_X);
            break;
        case Y:
            keyState=glfwGetKey(window, GLFW_KEY_Y);
            break;
        case Z:
            keyState=glfwGetKey(window, GLFW_KEY_Z);
            break;
        case ZERO:
            keyState=glfwGetKey(window, GLFW_KEY_0);
            break;
        case ONE:
            keyState=glfwGetKey(window, GLFW_KEY_1);
            break;
        case TWO:
            keyState=glfwGetKey(window, GLFW_KEY_2);
            break;
        case THREE:
            keyState=glfwGetKey(window, GLFW_KEY_3);
            break;
        case FOUR:
            keyState=glfwGetKey(window, GLFW_KEY_4);
            break;
        case FIVE:
            keyState=glfwGetKey(window, GLFW_KEY_5);
            break;
        case SIX:
            keyState=glfwGetKey(window, GLFW_KEY_6);
            break;
        case SEVEN:
            keyState=glfwGetKey(window, GLFW_KEY_7);
            break;
        case EIGHT:
            keyState=glfwGetKey(window, GLFW_KEY_8);
            break;
        case NINE:
            keyState=glfwGetKey(window, GLFW_KEY_9);
            break;
    }
    if (keyMonitors.find(key) == keyMonitors.end()) {
        keyMonitors[key] = new KeyMonitor(key);
    }
    if (keyMonitors[key]->currentFrame != frame) {
        keyMonitors[key]->lastState = keyMonitors[key]->thisState;
        keyMonitors[key]->currentFrame = frame;
    }
    keyMonitors[key]->thisState = keyState;
    if (keyMonitors[key]->lastState == keyState) {
        if (keyState) {
            return HOLD;
        }
        return UNHELD;
    }
    if (keyState) {
        return PRESS;
    }
    return RELEASE;
}
