#include "niz.hpp"
#include "dinstring.hpp"

int main()
{
    cout << "Niz celih brojeva duzine 10:" << endl;

    Niz<int,10> iNiz1, iNiz2;

    iNiz1.insertNiz(1);
    iNiz1.insertNiz(2);
    iNiz1.insertNiz(3);
    iNiz1.insertNiz(4);
    iNiz1.insertNiz(5);
    iNiz1.insertNiz(6);
    iNiz1.printNiz();

    iNiz2 = iNiz1;
    cout << endl;
    if(iNiz1 == iNiz2)
        cout << "iNiz1 i iNiz2 su jednaki" << endl;
    else
        cout << "iNiz1 i iNiz2 nisu jednaki" << endl;


    cout << endl;
    cout << "Niz stringova duzine 20:" << endl;
    Niz<DinString,20> dsNiz1, dsNiz2;

    dsNiz1.insertNiz("Jedan");
    dsNiz1.insertNiz("Dva");
    dsNiz1.insertNiz("Tri");
    dsNiz1.insertNiz("Cetiri");
    dsNiz1.insertNiz("Pet");
    dsNiz1.insertNiz("Sest");
    dsNiz1.printNiz();

    dsNiz2=dsNiz1;
    cout << endl;
    if(dsNiz1==dsNiz2)
        cout<<"dsNiz1 i dsNiz2 su jednaki"<<endl;
    else
        cout<<"dsNiz1 i dsNiz2 nisu jednaki"<<endl;

    return 0;
}
