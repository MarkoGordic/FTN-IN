#ifndef VIDEOKAMERA_H_INCLUDED
#define VIDEOKAMERA_H_INCLUDED

#include "kamera.hpp"

class VideoKamera : public Kamera
{
    protected:
        static int videoCounter;

    public:
        VideoKamera() : Kamera() {} // moze i samo VideoKamera() {}

        VideoKamera(int mp, int fsp) : Kamera(mp, fsp) {}

        int getVideoCounter() const
        {
            return videoCounter;
        }

        bool snimaj(int sekunde)
        {
			bool ret = false;
            if (sekunde * megaPikseli <= freeSpace){
                freeSpace-= sekunde * megaPikseli;
                videoCounter++;
                ret = true;
            }
			return ret;
        }

};


#endif // VIDEOKAMERA_H_INCLUDED
