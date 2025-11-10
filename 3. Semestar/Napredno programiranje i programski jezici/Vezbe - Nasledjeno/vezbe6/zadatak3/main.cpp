#include <iostream>

using namespace std;

#include "dinstring.hpp"
#include "kamera.hpp"
#include "videokamera.hpp"
#include "telefon.hpp"
#include "telefongen2.hpp"
#include "telefongen3.hpp"

int main()
{
    cout << "Kamera testiranje" << endl;
    Kamera k1, k2(3, 6), k3(k2);
    cout << "Uslikano slika: " << k1.getPhotoCounter() << endl;
    cout << (k2.slikaj() ? "true" : "false") << endl;
    cout << (k2.slikaj() ? "true" : "false") << endl;
    cout << (k2.slikaj() ? "true" : "false") << endl;
    cout << "Uslikano slika: " << k1.getPhotoCounter() << endl;

    cout << endl << "Video kamera testiranje" << endl;
    VideoKamera vk1, vk2(128, 512);
    cout << "Snimljeno videa: " << vk1.getVideoCounter() << endl;
    cout << (vk2.snimaj(5) ? "true" : "false") << endl;
    cout << (vk2.snimaj(4) ? "true" : "false") << endl;
    cout << (vk2.snimaj(1) ? "true" : "false") << endl;
    cout << "Snimljeno videa: " << vk1.getVideoCounter() << endl;

    cout << endl << "Telefon testiranje" << endl;
    Telefon t1, t2("22-333-444");
    cout << (t2.pozovi("22-333-444") ? "true" : "false") << endl;
    cout << (t2.pozovi("22-444") ? "true" : "false") << endl;

    cout << endl << "Telefon gen2 testiranje" << endl;
    TelefonGen2 t21, t22("653-12", 5, 20);
    cout << (t22.pozovi("22-333-444") ? "true" : "false") << endl;
    cout << (t22.slikajSliku() ? "true" : "false") << endl;
    cout << "Uslikano slika: " << t22.getPhotoCounter() << endl;

    cout << endl << "Telefon gen3 testiranje" << endl;
    TelefonGen3 t31, t32("53-12", 5, 20);
    cout << (t32.pozovi("22-333-444") ? "true" : "false") << endl;
    cout << (t32.slikajSliku() ? "true" : "false") << endl;
    cout << (t32.snimiVideo(5) ? "true" : "false") << endl;
    cout << (t32.snimiVideo(4) ? "true" : "false") << endl;
    cout << (t32.snimiVideo(1) ? "true" : "false") << endl;
    cout << "Uslikano slika: " << t32.getPhotoCounter() << endl;
    cout << "Snimljeno videa: " << t32.getVideoCounter() << endl;

    return 0;
}
