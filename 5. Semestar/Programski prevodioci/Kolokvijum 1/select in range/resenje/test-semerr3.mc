//OPIS: GRESKA - nevalidan opseg (prvi literal veci od treceg)
int main() {
    int a;
    select a in (100, 50, 10);
    return 0;
}
