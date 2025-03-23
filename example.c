#include <stdio.h>

#define CPF_CNPJ_IMPLEMENTATION
#include "cpf_cnpj.h"

int
main (int argc, char **argv)
{
    char const *cpf0 = "062.692.500-21", /* Random valid CPF example. */
               *cpf1 = "11111111111",    /* Invalid CPF example: All repeated digits. */
		       *cpf2 = "574.2548-20",    /* Invalid CPF example: Missing digits. */
               *cnpj0 = "71.028.186/0001-35", /* Random valid CNPJ example. */
		       *cnpj1 = "11.123.444/1111-20"; /* Invalid CNPJ example. */

    printf("CPF %s is %s\n", cpf0, (cpf_check(cpf0) == 0) ? "valid" : "not valid");
    printf("CPF %s is %s\n", cpf1, (cpf_check(cpf1) == 0) ? "valid" : "not valid");
    printf("CPF %s is %s\n", cpf2, (cpf_check(cpf2) == 0) ? "valid" : "not valid");
    printf("CNPJ %s is %s\n", cnpj0, (cnpj_check(cnpj0) == 0) ? "valid" : "not valid");
    printf("CNPJ %s is %s\n", cnpj1, (cnpj_check(cnpj1) == 0) ? "valid" : "not valid");
    
    return 0;
}
