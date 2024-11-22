#ifndef KAMERA_HPP_INCLUDED
#define KAMERA_HPP_INCLUDED

class Kamera {
protected:
    int megaPikseli;
    int freeSpace;
    static int photoCounter;
public:
    Kamera() : megaPikseli(0), freeSpace(0) {}
    Kamera(int megaPikseli, int freeSpace) : megaPikseli(megaPikseli), freeSpace(freeSpace) {}
    Kamera(const Kamera &k) : megaPikseli(k.megaPikseli), freeSpace(k.freeSpace) {}

    bool slikaj() {
        if (freeSpace > 0) {
            freeSpace--;
            photoCounter++;
            return true;
        }
        return false;
    }

    static int getPhotoCounter() {
        return photoCounter;
    }
};

int Kamera::photoCounter = 0;

#endif // KAMERA_HPP_INCLUDED