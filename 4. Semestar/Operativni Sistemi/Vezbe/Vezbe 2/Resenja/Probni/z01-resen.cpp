/*
 * Zadatak 1: XOR program za kodiranje
 * Napisati program koji za dato ime fajla na komandnoj liniji napravi novi fajl
 * sa istim imenom i ekstrenzijom .enc. Taj fajl se sastoji od svako bajta
 * ulaznog fajla XOR-ovanog sa unetim PIN-om koji ima 1 bajt i vrednosti od 1 do
 * 255.
 * */

#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

int main(int argc, char **argv) {
  if (argc < 2) {
    cout << "Potrebno mi je ime fajla." << endl;
    return 1;
  }
  string fname(argv[1]);
  string outname = fname + ".enc";
  unsigned char pin = 0;
  int ipin = 0;
  do {
    cout << "PIN (1-255): ";
    cin >> ipin;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (ipin <= 0 || ipin > 255);
  pin = (unsigned char)ipin;

  char in = 0;
  ifstream inf(fname, std::ios::in | std::ios::binary);
  ofstream outf(outname, std::ios::out | std::ios::binary);

  while (true) {
    inf.read(&in, 1);
    if (!inf.good()) {
      break;
    }
    in = in ^ pin;
    outf.write(&in, 1);
  }
  inf.close();
  outf.close();
  return 0;
}
