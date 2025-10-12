// Gabriel Santos de Andrade   RA 815407
// Leonardo Prado Silva        RA 813169

#include <stdio.h>

long long square_and_mult(long long base, long long expoente, long long modulo) {
    long long result = 1;
    base = base % modulo;
    
    while (expoente > 0) {
        if (expoente & 1)
            result = (result * base) % modulo;
        base = (base * base) % modulo;
        expoente >>= 1;
    }
    
    return result;
}

int main() {
    long long x, n, k;
    scanf("%lld %lld %lld", &x, &k, &n);
    printf("%lld\n", square_and_mult(x, k, n));
    
    return 0;
}