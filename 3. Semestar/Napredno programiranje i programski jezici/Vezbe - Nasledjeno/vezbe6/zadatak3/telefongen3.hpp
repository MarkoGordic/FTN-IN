#ifndef TELEFONGEN3_HPP_INCLUDED
#define TELEFONGEN3_HPP_INCLUDED

class TelefonGen3 : public TelefonGen2 {
private:
    VideoKamera vk;
public:
    TelefonGen3 () : TelefonGen2 (), vk () {}

    TelefonGen3 (const DinString& br, int mp, int fs) : TelefonGen2 (br, mp, fs), vk(mp, fs) {}

    int getVideoCounter () const {
        return vk.getVideoCounter();
    }

    bool snimiVideo (int sec) {
        return vk.snimaj(sec);
    }
};

#endif // TELEFONGEN3_HPP_INCLUDED
