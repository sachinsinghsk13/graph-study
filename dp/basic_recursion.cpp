#include <bits/stdc++.h>


long factorial(long n) {
    if (n == 1) return 1;
    return n * factorial(n - 1);
}

long fibbonaci(long n) {
    if (n == 0 || n == 1) return n;
    return fibbonaci(n - 1) + fibbonaci(n - 2);
}