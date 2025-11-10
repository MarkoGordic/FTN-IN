#include "dinstring.hpp"

DinString::DinString() {
    duzina = 0;
    text = NULL;
}

DinString::DinString(const char ulaz[]) {
    duzina = 0;
    while(ulaz[duzina] != '\0')
        duzina++;

    text = new char[duzina + 1];
    for(int i = 0; i < duzina; i++)
        text[i] = ulaz[i];

    text[duzina] = '\0';
}

DinString::DinString(const DinString& ds) {
    duzina = ds.duzina;

    text = new char[duzina + 1];
    for(int i = 0; i < duzina; i++)
        text[i] = ds.text[i];

    text[duzina] = '\0';
}

DinString::~DinString() {
    delete[] text;
}

int DinString::length() const {
    return duzina;
}

char& DinString::operator[] (int i) {
    return text[i];
}

char DinString::operator[] (int i) const {
    return text[i];
}

DinString& DinString::operator=(const DinString& ds) {
    if(this != &ds) {
        delete[] text;
        duzina = ds.duzina;
        text = new char[duzina + 1];
        for (int i = 0; i < duzina; i++)
            text[i] = ds.text[i];

        text[duzina] = '\0';
    }

    return *this;
}

DinString& DinString::operator+=(const DinString& ds) {
    int i;
    char *tempText = new char[duzina + ds.duzina + 1];
    for (i = 0; i < duzina; i++)
        tempText[i] = text[i];
    for (i = 0; i < ds.duzina; i++)
        tempText[duzina + i] = ds.text[i];
    tempText[duzina + ds.duzina] = '\0';

    duzina += ds.duzina;

    delete[] text;
    text = tempText;

    return *this;
}

bool operator==(const DinString& ds1, const DinString& ds2){
    if(ds1.duzina != ds2.duzina)
        return false;

    for(int i = 0; i < ds1.duzina; i++)
        if(ds1.text[i] != ds2.text[i])
            return false;

    return true;
}

bool operator!=(const DinString& ds1, const DinString& ds2){
    if(ds1.duzina != ds2.duzina)
        return true;

    for(int i = 0; i < ds1.duzina; i++)
        if(ds1.text[i] != ds2.text[i])
            return true;

    return false;
}

DinString operator+(const DinString& ds1, const DinString& ds2){
    DinString temp;
    temp.duzina = ds1.duzina + ds2.duzina;

    temp.text = new char[temp.duzina + 1];

    int i;
    for(i = 0; i < ds1.duzina; i++)
        temp.text[i] = ds1.text[i];

    for(i = 0; i < ds2.duzina; i++)
        temp.text[ds1.duzina + i] = ds2.text[i];
    temp.text[temp.duzina] = '\0';

    return temp;

}



ostream& operator<<(ostream& out, const DinString& ds) {
    if(ds.duzina > 0)
        out << ds.text;

    return out;
}
