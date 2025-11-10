#ifndef VIDEOKAMERA_HPP_INCLUDED
#define VIDEOKAMERA_HPP_INCLUDED

class VideoKamera : public Kamera {
private:
    static int videoCounter;
public:
    VideoKamera () : Kamera () {}

    VideoKamera (int mp, int fs) : Kamera (mp, fs) {}

    int getVideoCounter () const {
        return videoCounter;
    }

    bool snimaj (int sekunde) {
        if (freeSpace - sekunde * megaPikseli >= 0) {
            freeSpace -= (sekunde * megaPikseli);
            videoCounter++;
            return true;
        }
        return false;
    }
};

int VideoKamera::videoCounter = 0;

#endif // VIDEOKAMERA_HPP_INCLUDED
