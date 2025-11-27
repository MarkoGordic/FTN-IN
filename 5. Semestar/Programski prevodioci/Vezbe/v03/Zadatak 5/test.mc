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

  a++;

  for i = 1 downto 10
    a = a + 1;
  next i

  do {
    a = 5;
    a++;
  } while(a > 3);

  return abs(-5);
}
