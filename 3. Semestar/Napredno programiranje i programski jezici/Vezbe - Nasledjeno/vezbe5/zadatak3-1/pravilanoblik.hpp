#ifndef PRAVILANOBLIK_HPP_INCLUDED
#define PRAVILANOBLIK_HPP_INCLUDED

class PravilanOblik : public Oblik {
public:
    PravilanOblik (double a = 4) : Oblik(a, a) {}
    PravilanOblik (const PravilanOblik& oblik) : Oblik((Oblik)oblik) {}
};

#endif // PRAVILANOBLIK_HPP_INCLUDED
