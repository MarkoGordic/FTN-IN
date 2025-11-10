#ifndef KAMERA_HPP_INCLUDED
#define KAMERA_HPP_INCLUDED

class Kamera {
protected:
    int megaPikseli;
    int freeSpace;
    static int photoCounter;
public:
    Kamera () : megaPikseli (2), freeSpace (10) {}

    Kamera (int megaPikseli, int freeSpace) {
        this->megaPikseli = megaPikseli;
        this->freeSpace = freeSpace;
    }

    Kamera (const Kamera & k) {
        megaPikseli = k.megaPikseli;
        freeSpace = k.freeSpace;
    }

    int getPhotoCounter () const {
        return photoCounter;
    }

    bool slikaj () {
        if (freeSpace - megaPikseli >= 0) {
            freeSpace -= megaPikseli;
            photoCounter++;
            return true;
        }
        return false;
    }
};

int Kamera::photoCounter = 0;

#endif // KAMERA_HPP_INCLUDED
