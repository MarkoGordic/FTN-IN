#ifndef GRAD_HPP_INCLUDED
#define GRAD_HPP_INCLUDED

class Grad {
private:
    DinString naziv;
    List <Prodavnica*> prodavnice;
public:
    Grad () : naziv() {}

    Grad (const char* ime) : naziv(ime) {}

    Grad (const DinString& ime) : naziv(ime) {}

    bool dodajProdavnicu (Prodavnica& prod) {
        return prodavnice.add(prodavnice.size() + 1, &prod);
    }

    void ispisiNajjeftinijuProdavnicu () {
        if (prodavnice.empty())
            cout << "Nema prodavnica u gradu!" << endl;

        Prodavnica* prod;
        Prodavnica* minP;
        prodavnice.read(1, minP);
        for (int i = 2; i <= prodavnice.size(); i++) {
            prodavnice.read(i, prod);
            if (prod->getRrosecnaCenaProizvoda() < minP->getRrosecnaCenaProizvoda())
                minP = prod;
        }
        cout << "Najjeftinija prodavnica je: " << endl;
        cout << *minP << endl;
    }
};

#endif // GRAD_HPP_INCLUDED
