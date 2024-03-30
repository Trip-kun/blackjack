#pragma once

template <typename T> class Element {
public:
    virtual ~Element() = default;
    virtual void Click(double button, double x, double y, T t) = 0;
    virtual void Release(double button, double x, double y, T t) = 0;
};
