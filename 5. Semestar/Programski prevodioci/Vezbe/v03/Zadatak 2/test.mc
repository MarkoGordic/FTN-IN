int abs(int i) {
  int res, res1, res2;
  if(i < 0)
    res = 0 - i;
  else 
    res = i;
  return res;
}

int main() {
  select a, b, c from d where (a > b);
  return abs(-5);
}
