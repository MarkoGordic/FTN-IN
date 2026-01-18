//OPIS: ugnjezden while
//RETURN: 5

int x;

int main() {
 int a;
 int b;
 a = 1;
 b = 1;
 while ( a < 3){
   a = a +  3; // a postaje 4
   while ( b < 3)
     b = b +  a; // b postaje 5 
 }
 
 return b;
}




