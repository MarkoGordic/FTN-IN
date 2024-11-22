#ifndef VIDEO_KAMERA_HPP_INCLUDED
#define VIDEO_KAMERA_HPP_INCLUDED

#include "Kamera.hpp"

class VideoKamera : public Kamera {
private:
    static int videoCounter;
public:
    VideoKamera() : Kamera() {}
    VideoKamera(int megaPikseli, int freeSpace) : Kamera(megaPikseli, freeSpace) {}
    VideoKamera(const VideoKamera &vk) : Kamera(vk) {}

    bool snimaj(int sec) {
        if (freeSpace > sec) {
            freeSpace -= sec;
            videoCounter++;
            return true;
        }
        return false;
    }

    static int getVideoCounter() {
        return videoCounter;
    }
};

int VideoKamera::videoCounter = 0;

#endif // VIDEO_KAMERA_HPP_INCLUDED