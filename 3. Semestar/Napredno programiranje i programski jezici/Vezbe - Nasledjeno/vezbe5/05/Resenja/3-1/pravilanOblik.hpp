#ifndef PRAVILANOBLIK_DEF
#define PRAVILANOBLIK_DEF

#include "oblik.hpp"

class PravilanOblik : public Oblik
{
    public:
        PravilanOblik(double aa = 4) : Oblik(aa, aa) {}

        PravilanOblik(const PravilanOblik& po) : Oblik((Oblik)po) {}
};

#endif
