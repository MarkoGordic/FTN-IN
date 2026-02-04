//OPIS: iterate
//RETURN: 70
int main(){
  int x;
  int y;
  y=0;
  iterate x 3 to 20 {
    y = x + y;
  }
  return y;
}

