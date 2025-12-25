//OPIS: GRESKA - srednji literal nije u opsegu (5 nije izmedju 10 i 20)
int main() {
    int x;
    select x in (10, 5, 20);
    return 0;
}
