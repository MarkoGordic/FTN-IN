#ifndef TELEFONGEN3_HPP_INCLUDED
#define TELEFONGEN3_HPP_INCLUDED

#include "TelefonGen2.hpp"
#include "VideoKamera.hpp"

class TelefonGen3 : public TelefonGen2 {
private:
    VideoKamera vk;
public:
    TelefonGen3() : TelefonGen2(), vk() {}
    TelefonGen3(DinString broj, int megaPikseli, int freeSpace, int videoSpace) : TelefonGen2(broj, megaPikseli, freeSpace), vk(megaPikseli, videoSpace) {}

    bool snimiVideo(int sec){
        return vk.snimaj(sec);
    }
};

#endif // TELEFONGEN3_HPP_INCLUDED