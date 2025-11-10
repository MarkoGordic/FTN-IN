#ifndef KAMERA_H_INCLUDED
#define KAMERA_H_INCLUDED

class Kamera
{
    protected:
        int megaPikseli;
        int freeSpace;
        static int photoCounter;

    public:
        Kamera()
        {
            megaPikseli = 1;
            freeSpace = 10;
        }

        Kamera(int mp, int fsp)
        {
            megaPikseli = mp;
            freeSpace = fsp;
        }

        Kamera(const Kamera& kk)
        {
            megaPikseli = kk.megaPikseli;
            freeSpace = kk.freeSpace;
        }

        int getPhotoCounter() const
        {
            return photoCounter;
        }

        bool slikaj()
        {
			bool ret = false;
            if (freeSpace - megaPikseli >= 0){
                freeSpace -= megaPikseli;
                photoCounter++;
                ret = true;
            }
			return ret;
        }

};

#endif // KAMERA_H_INCLUDED
