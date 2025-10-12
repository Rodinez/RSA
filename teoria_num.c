// Gabriel Santos de Andrade   RA 815407
// Leonardo Prado Silva        RA 813169

#include <stdio.h>

void eea(long long a, long long b, long long *mdc, long long *x, long long *y) {
    long long s0 = 1, s1 = 0;
    long long t0 = 0, t1 = 1;
    long long r0 = b, r1 = a;

    long long q, r_temp, s_temp, t_temp;
    while (r1 != 0) {
        q = r0 / r1;

        r_temp = r1;
        r1 = r0 - q * r1;
        r0 = r_temp;
        
        s_temp = s1;
        s1 = s0 - q * s1;
        s0 = s_temp;
        
        t_temp = t1;
        t1 = t0 - q * t1;
        t0 = t_temp;
    }
    
    *mdc = r0;
    *x = s0;
    *y = t0;
}

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
    char linha[100];
    long long x, k, n;

    if (!fgets(linha, sizeof(linha), stdin))
        return 1;

    int count = sscanf(linha, "%lld %lld %lld", &x, &k, &n);

    if (count == 2) {
        n = k;
        long long gcd, inverso, y;
        eea(x, n, &gcd, &inverso, &y);

        if (gcd == 1) {
            inverso = (inverso % n + n) % n;
            printf("%lld %lld\n", gcd, inverso);
        } else {
            printf("%lld N\n", gcd);
        }
    } 
    else if (count == 3) {
        printf("%lld\n", square_and_mult(x, k, n));
    } 
}
