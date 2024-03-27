#pragma once

namespace tween {
    inline double linear(double time, double start, double end, double duration) {
        if (time<0) {
            return start;
        }
        if (time>duration) {
            return end;
        }
        return start + (end-start)*time/duration;
    }
    inline double easeInQuad(double time, double start, double end, double duration) {
        if (time<0) {
            return start;
        }
        if (time>duration) {
            return end;
        }
        time /= duration;
        return start + (end-start)*time*time;
    }
    inline double easeOutQuad(double time, double start, double end, double duration) {
        if (time<0) {
            return start;
        }
        if (time>duration) {
            return end;
        }
        time /= duration;
        return start + (end-start)*time*(2-time);
    }
inline double easeInOutQuad(double time, double start, double end, double duration) {
        if (time<0) {
            return start;
        }
        if (time>duration) {
            return end;
        }
        time /= duration/2;
        if (time < 1) {
            return start + (end-start)/2*time*time;
        }
        time--;
        return start + (end-start)/2*(time*(time-2)-1);
    }

}