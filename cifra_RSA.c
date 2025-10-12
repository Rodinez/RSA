// Gabriel Santos de Andrade   RA 815407
// Leonardo Prado Silva        RA 813169
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


void square_and_mult(mpz_t result, mpz_t base, mpz_t expoente, mpz_t modulo) {
    mpz_t base_temp, exp_temp;
    mpz_inits(base_temp, exp_temp, NULL);
    
    mpz_set_ui(result, 1);    
    mpz_mod(base_temp, base, modulo);
    mpz_set(exp_temp, expoente);
    
    while (mpz_cmp_ui(exp_temp, 0) > 0) {
        //verifica se é ímpar
        if (mpz_odd_p(exp_temp)) {
            //result = (result * base) % modulo
            mpz_mul(result, result, base_temp);
            mpz_mod(result, result, modulo);
        }
        
        mpz_mul(base_temp, base_temp, base_temp);
        mpz_mod(base_temp, base_temp, modulo);
        
        //expoente >>= 1 (shift right - divisão por 2)
        mpz_fdiv_q_ui(exp_temp, exp_temp, 2);
    }
    
    mpz_clears(base_temp, exp_temp, NULL);
}

int main() {
    char base_str[10], n_str[4096], exp_str[4096], msg_str[4096];
    int base;
    
    printf("Digite a base (10 ou 16): ");
    fgets(base_str, sizeof(base_str), stdin);
    base = atoi(base_str);
    
    if (base != 10 && base != 16) {
        printf("Erro: Base deve ser 10 ou 16\n");
        return 1;
    }
    
    printf("Digite o modulo (n): ");
    fgets(n_str, sizeof(n_str), stdin);
    n_str[strcspn(n_str, "\n")] = 0; //remove quebra de linha
    
    printf("Digite o expoente (e ou d): ");
    fgets(exp_str, sizeof(exp_str), stdin);
    exp_str[strcspn(exp_str, "\n")] = 0;
    
    printf("Digite a mensagem (m ou c): ");
    fgets(msg_str, sizeof(msg_str), stdin);
    msg_str[strcspn(msg_str, "\n")] = 0;
    
    //inicializar variáveis GMP
    mpz_t n, exp, msg, result;
    mpz_inits(n, exp, msg, result, NULL);
    
    //converter strings para números GMP
    mpz_set_str(n, n_str, base); 
    mpz_set_str(exp, exp_str, base);
    mpz_set_str(msg, msg_str, base);
    
    //verificar se mensagem < n
    if (mpz_cmp(msg, n) >= 0) {
        printf("Erro: Mensagem deve ser menor que o modulo\n");
        mpz_clears(n, exp, msg, result, NULL);
        return 1;
    }

    square_and_mult(result, msg, exp, n);
    
    printf("\nRESULTADO\n\n");
    printf("Base\n%d\n\n", base);
    printf("Mensagem\n");
    mpz_out_str(stdout, base, result);
    printf("\n");
    
    // Limpar variáveis
    mpz_clears(n, exp, msg, result, NULL);
    
    return 0;
}