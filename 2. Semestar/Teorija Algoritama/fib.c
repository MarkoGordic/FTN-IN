// recursive fibonacci for n

int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

// dynamic programming fibonacci

int fib_dynamic(int n) {
    int niz_fib[n + 1];

    niz_fib[0] = 0;
    niz_fib[1] = 1;

    for(int i = 2; i <= n; i++){
        niz_fib[i] = niz_fib[i - 1] + niz_fib[i - 2];
    }

    return niz_fib[n];
}