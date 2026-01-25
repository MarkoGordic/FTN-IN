//OPIS: ispravan postinkrement
//RETURN: 53

int main() {
int x;
int y;
x = 3;
y = x++ + x++ + 42;
return x + y;
}