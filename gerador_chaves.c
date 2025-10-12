// Gabriel Santos de Andrade   RA 815407
// Leonardo Prado Silva        RA 813169
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

void eea(mpz_t a, mpz_t b, mpz_t mdc, mpz_t x, mpz_t y) {
    mpz_t s0, s1, t0, t1, r0, r1;
    mpz_t q, r_temp, s_temp, t_temp;
    
    mpz_inits(s0, s1, t0, t1, r0, r1, q, r_temp, s_temp, t_temp, NULL);
    
    // Inicialização
    mpz_set_ui(s0, 1);
    mpz_set_ui(s1, 0);
    mpz_set_ui(t0, 0);
    mpz_set_ui(t1, 1);
    mpz_set(r0, b);
    mpz_set(r1, a);
    
    while (mpz_cmp_ui(r1, 0) != 0) {
        // q = r0 / r1
        mpz_fdiv_q(q, r0, r1);
        
        // r_temp = r1
        // r1 = r0 - q * r1
        // r0 = r_temp
        mpz_set(r_temp, r1);
        mpz_mul(r1, q, r1);
        mpz_sub(r1, r0, r1);
        mpz_set(r0, r_temp);
        
        // s_temp = s1
        // s1 = s0 - q * s1
        // s0 = s_temp
        mpz_set(s_temp, s1);
        mpz_mul(s1, q, s1);
        mpz_sub(s1, s0, s1);
        mpz_set(s0, s_temp);
        
        // t_temp = t1
        // t1 = t0 - q * t1
        // t0 = t_temp
        mpz_set(t_temp, t1);
        mpz_mul(t1, q, t1);
        mpz_sub(t1, t0, t1);
        mpz_set(t0, t_temp);
    }
    
    mpz_set(mdc, r0);
    mpz_set(x, s0);
    mpz_set(y, t0);
    
    mpz_clears(s0, s1, t0, t1, r0, r1, q, r_temp, s_temp, t_temp, NULL);
}

int main() {
    int key_size, base;
    
    printf("Digite o tamanho da chave: ");
    scanf("%d", &key_size);
    
    printf("Digite a base: ");
    scanf("%d", &base);
    
    mpz_t p, q, n, phi, e, d, p_minus_1, q_minus_1, gcd_test, y_temp;
    mpz_inits(p, q, n, phi, e, d, p_minus_1, q_minus_1, gcd_test, y_temp, NULL);
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    int prime_bits = key_size / 2;
    
    printf("Gerando chaves RSA de %d bits\n", key_size);
    
    //Gerar primo p
    mpz_urandomb(p, state, prime_bits);
    mpz_nextprime(p, p);
    
    //Gerar primo q diferente de p
    do {
        mpz_urandomb(q, state, prime_bits);
        mpz_nextprime(q, q);
    } while (mpz_cmp(p, q) == 0);
    

    mpz_mul(n, p, q);
    
    //Calcular phi(n) = (p-1) * (q-1)
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_mul(phi, p_minus_1, q_minus_1);
    
    //Escolha do e 655537, o mais comum
    mpz_set_ui(e, 65537);
    
    eea(e, phi, gcd_test, d, y_temp);
    

    mpz_mod(d, d, phi);
    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, phi);
    }
    
    printf("\nCHAVES GERADAS\n\n");
    
    printf("Base:\n%d\n\n", base);
    
    printf("Modulo:\n");
    mpz_out_str(stdout, base, n);
    printf("\n");
    
    printf("Expoente_publico:\n");
    mpz_out_str(stdout, base, e);
    printf("\n");
    
    printf("Expoente_privado:\n");
    mpz_out_str(stdout, base, d);
    printf("\n");
    
    printf("Primo_p:\n");
    mpz_out_str(stdout, base, p);
    printf("\n");
    
    printf("Primo_q:\n");
    mpz_out_str(stdout, base, q);
    printf("\n");
    
    mpz_clears(p, q, n, phi, e, d, p_minus_1, q_minus_1, gcd_test, y_temp, NULL);
    gmp_randclear(state);
    
    return 0;
}