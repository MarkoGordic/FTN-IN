#ifndef PUTNIKDETE_HPP_INCLUDED
#define PUTNIKDETE_HPP_INCLUDED

class PutnikDete : public Putnik {
private:
    DinString mbRoditelja;
public:
    PutnikDete() : Putnik(), mbRoditelja("") {}

    PutnikDete(int bk, VrstaKarte v, const DinString& mb, const DinString& i, const DinString& mbr)
        : Putnik(bk,v,mb,i), mbRoditelja(mbr) {}

    PutnikDete(const Putnik& p, const DinString& mbr) : Putnik(p), mbRoditelja(mbr) {}

    DinString toString() const {
        return "Dete: " + Putnik::toString() + " " + mbRoditelja;
    }
};

#endif // PUTNIKDETE_HPP_INCLUDED
