#ifndef PUTNIKDETE_HPP_INCLUDED
#define PUTNIKDETE_HPP_INCLUDED

class PutnikDete : public Putnik {
private:
    DinString mbRoditelja;
public:
    PutnikDete() {}

    PutnikDete(int bk, VrstaKarte vk, const DinString& m, const DinString& i, const DinString& mr) :
        Putnik(bk, vk, m, i), mbRoditelja(mr) {}

    PutnikDete(const Putnik& p, const DinString& mbr) : Putnik(p), mbRoditelja(mb) {}

    DinString toString() const {
        return "Dete: " + Putnik::toString() + " " + mbRoditelja;
    }
};

#endif // PUTNIKDETE_HPP_INCLUDED
