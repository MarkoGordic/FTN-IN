#include "telefonGen3.hpp"

int Kamera::photoCounter = 0;
int VideoKamera::videoCounter = 0;

int main()
{
    cout << "Testiranje klase Kamera" << endl << endl;

    Kamera k, k1(128, 1000), k2(k1);
    cout << "Trenutno uslikanih slika: " << k.getPhotoCounter() << endl;

    if(k.slikaj()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    if(k1.slikaj()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    if(k2.slikaj()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    cout << "Trenutno uslikanih slika: " << k.getPhotoCounter() << endl;



    cout << endl << endl << "Testiranje klase VideoKamera" << endl << endl;

    VideoKamera vk, vk1(128, 1000);
    cout << "Trenutno snimljenih videa: " << vk.getVideoCounter() << endl;

    if(vk.snimaj(3)) {
        cout << "Uspesno snimanje." << endl;
    } else {
        cout << "Neuspesno snimanje." << endl;
    }

    if(vk1.snimaj(11)) {
        cout << "Uspesno snimanje." << endl;
    } else {
        cout << "Neuspesno snimanje." << endl;
    }

    cout << "Trenutno snimljenih videa: " << vk.getVideoCounter() << endl;


    cout << endl << endl << "Testiranje klase Telefon" << endl << endl;

    Telefon t, t1("111-222");

    if(t.pozovi("22-333")) {
        cout << "Broj 22-333 uspesno pozvao broj 22-333." << endl;
    } else {
        cout << "Broj 22-333 neuspesno pozvao broj 22-333." << endl;
    }

    if(t1.pozovi("222-333")) {
        cout << "Broj 111-222 uspesno pozvao broj 222-333." << endl;
    } else {
        cout << "Broj 111-222 neuspesno pozvao broj 222-333." << endl;
    }



    cout << endl << endl << "Testiranje klase TelefonGen2" << endl << endl;

    TelefonGen2 tg, tg1(128, 1000, "111-222");
    cout << "Trenutno uslikanih slika: " << tg.getPhotoCounter() << endl;

    if(tg.slikajSliku()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    if(tg1.slikajSliku()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    cout << "Trenutno uslikanih slika: " << tg.getPhotoCounter() << endl;



    cout << endl << endl << "Testiranje klase TelefonGen3" << endl << endl;

    TelefonGen3 tgg, tgg1(2, 200, "061666999");
    cout << "Trenutno uslikanih slika: " << tgg.getPhotoCounter() << endl;
    cout << "Trenutno snimljenih videa: " << tgg.getVideoCounter() << endl;

    if(tgg.slikajSliku()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    if(tgg1.slikajSliku()) {
        cout << "Uspesno slikanje." << endl;
    } else {
        cout << "Neuspesno slikanje." << endl;
    }

    if(tgg.snimiVideo(3)) {
        cout << "Uspesno snimanje." << endl;
    } else {
        cout << "Neuspesno snimanje." << endl;
    }

    if(tgg1.snimiVideo(10)) {
        cout << "Uspesno snimanje." << endl;
    } else {
        cout << "Neuspesno snimanje." << endl;
    }

    cout << "Trenutno uslikanih slika: " << tgg.getPhotoCounter() << endl;
    cout << "Trenutno snimljenih videa: " << tgg.getVideoCounter() << endl;


    return 0;
}
