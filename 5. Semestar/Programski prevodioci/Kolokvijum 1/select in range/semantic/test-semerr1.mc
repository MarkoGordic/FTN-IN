//OPIS: GRESKA - nedeklarisana promenljiva u select
int main() {
    int a;
    select a, b in (0, 5, 10);
    return 0;
}
