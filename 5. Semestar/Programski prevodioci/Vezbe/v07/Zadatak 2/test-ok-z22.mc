//OPIS: dva while-a jedan ispod drugog
//RETURN: 5

int x;

int main() {
 int a;
 int b;
 a = 1;
 b = 1;
 while ( a < 3)
        a = a +  3;

 while ( b < 3)
        b = b +  a; //a je u ovom trnutku 4
 return b;
}




