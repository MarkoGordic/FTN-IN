/*
    Uz zadatke ide fajl koji se zove ulaz.txt
    U njemu se nalaze bodovi studenata u formi:
    Ime,Prezime,V=70&P=30,Beleska
    Napraviti program koji na osnovu fajla sračuna prosek za V (vežbe) i prosek za 
    P(ispit). 
*/

#include <iostream>
#include <regex>
#include <fstream>

using namespace std;

int main(){
    fstream f("ulaz.txt");
    regex r(".+,.+,V=(\\d+)&P=(\\d+),.+");
    smatch m;
    char buff[160] = {0};
    double p = 0;
    double v = 0;
    int count = 0;
    while(!f.eof()){
        f.getline(buff, 159, '\n');
        string s(buff);
        if(regex_search(s, m, r)){
            v += atoi(m[1].str().c_str());
            p += atoi(m[2].str().c_str());
            count++;
        }
    }
    p /= count;
    v /= count;
    cout << "Prosek za P je " << p << ", a za V je " << v << endl;
    return 0;
}