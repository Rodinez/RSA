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

int main() {
    long long x, n;
    scanf("%lld %lld", &x, &n);
    long long mdc = 0, inverso = 0;
    eea(x, n, &mdc, &inverso, &inverso);
    
    if (mdc == 1) {
        // Ajusta o inverso para ser positivo
        inverso = (inverso % n + n) % n;
        printf("%lld %lld\n", mdc, inverso);
    } else {
        printf("%lld N\n", mdc);
    }
    
    return 0;
}