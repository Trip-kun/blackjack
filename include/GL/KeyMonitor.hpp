#pragma once
#include <map>
#include <GLFW/glfw3.h>
enum Key {
    ESCAPE,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE
};
enum KeyMode {
    PRESS, RELEASE, HOLD, UNHELD
};
class KeyFrame {}; // Used to tell when frames have changed without timing.
class KeyMonitor {
    static std::map<Key, KeyMonitor*> keyMonitors;
    Key key;
    explicit KeyMonitor(Key key);
    bool lastState;
    bool thisState;
    KeyFrame* currentFrame;
public:
    static KeyMode getState(GLFWwindow* window, KeyFrame* frame, Key key);
    static void Clean();
};