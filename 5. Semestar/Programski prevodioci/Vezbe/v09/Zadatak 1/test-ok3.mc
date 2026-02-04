//OPIS: ugnjezdeni iterate
//RETURN: 132
int main(){
  int x;
  int y;
  int i;
  y=0;
  iterate x 1 to 3 {
      iterate i 2 to 4 {
          y = y + y + i;
      }
    y = x + y;
  }
  return y;
}

