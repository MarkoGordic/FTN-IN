//OPIS: dve petlje između iskaza
int main() {
    int a;
    unsigned b;
    if (a == 0)
        b = 5u;
    do
      b = b + 1u;
    while (b < 100u);
    do
      a = a + 1;
    while (a < 100);
    if (b == 10u)
        a = 5;
    a = a - 30;
}

