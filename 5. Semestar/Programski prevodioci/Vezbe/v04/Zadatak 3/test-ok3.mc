//OPIS: dve petlje unutar if-a
int main() {
    int a;
    unsigned b;
    if (a == 0)
        do
          a = a + 1;
        while (a < 100);
    else
        do
          b = b + 1u;
        while (b < 100u);
}

