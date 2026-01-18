//OPIS: dve globalne promenljive
//RETURN: 202

int x;
int y;

int f1(int a) {
    x = a;
    return x;
}

int f2(int a) {
    y = a + x;
    return y;
}

int main() {
  int a;
  int b;
  a = f1(42);
  b = f2(17);
  return a + b + x + y;
}

