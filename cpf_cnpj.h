#if !defined (CPF_CNPJ_H)
#define CPF_CNPJ_H

/**
 * Checks that a cstring is a valid CPF (Brazilian individual taxpayer registry),
 * ignoring all non-numeric characters.
 * @param cpf Null-terminated string containing the CPF to validate.
 * @returns 0 if the CPF is valid, negative otherwise.
 */
int cpf_check (char const *cpf);
/**
 * Checks that a cstring is a valid CNPJ (Brazilian corporate taxpayer registry),
 * ignoring all non-numeric characters.
 * @param CNPJ Null-terminated string containing the CNPJ to validate.
 * @returns 0 if the CNPJ is valid, negative otherwise.
 */
int cnpj_check (char const *cnpj);

#endif /* !defined (CPF_CNPJ_H) */

#if defined(CPF_CNPJ_IMPLEMENTATION)

#define _CPF_CNPJ_ISDIGIT(c) (('0' <= (c)) && ((c) <= '9'))
#define _CPF_CNPJ_ATOI(c) (int)((c) - '0')

int
cpf_check (char const  *cpf)
{
    int i, digits, number, all_equal, digit_10, digit_11, accum_10, accum_11;
    
    digits = 0, accum_10 = 0, accum_11 = 0;
    for (i = 0; cpf[i] != '\0'; ++i) {
        if (!_CPF_CNPJ_ISDIGIT(cpf[i])) continue; /* Skip non-numeric characters. */
        number = _CPF_CNPJ_ATOI(cpf[i]);
        
        if (++digits <= 9) { /* Accumulate the digits. */
            accum_10 += number * (11 - digits);
            accum_11 += number * (12 - digits);
        } else { /* Find the validation digits. */
            digit_10 = digit_11;
            digit_11 = number;
        }

        if      (i == 0)              all_equal = number;
        else if (all_equal != number) all_equal = -1; /* Detect when all digits are repeated. */
    }

    if (all_equal != -1) return -1; /* Filter all repeated digits edge case. */
    if (digits != 11)    return -1; /* All CPFs must have 11 digits. */
    
    accum_10 = 11 - (accum_10 % 11); /* Calculate the 10th digit. */
    if (accum_10 >= 10) accum_10 = 0;
    if (accum_10 != digit_10) return -1;

    accum_11 += accum_10 * 2;
    accum_11 = 11 - (accum_11 % 11); /* Calculate the 11th digit. */
    if (accum_11 >= 10) accum_11 = 0;
    if (accum_11 != digit_11) return -1;

    return 0;
}

int
cnpj_check (char const *cnpj)
{
    int i, digits, number, all_equal, digit_13, digit_14, accum_13, accum_14;

    digits = 0, accum_13 = 0, accum_14 = 0;
    for (i = 0; cnpj[i] != '\0'; ++i) {
        if (!_CPF_CNPJ_ISDIGIT(cnpj[i])) continue; /* Skip non-numeric characters. */
        number = _CPF_CNPJ_ATOI(cnpj[i]);

        if (++digits <= 12) { /* Accumulate the digits. */      
            accum_13 += number * ((digits <= 4 ? 6 : 14) - digits);
            accum_14 += number * ((digits <= 5 ? 7 : 15) - digits);
        } else { /* Find the validation digits. */
            digit_13 = digit_14;
            digit_14 = number;
        }

        if      (i == 0)              all_equal = number;
        else if (all_equal != number) all_equal = -1; /* Detect when all digits are repeated. */
    }

    if (all_equal != -1) return -1; /* Filter all repeated digits edge case. */
    if (digits != 14)    return -1; /* All CNPJs must have 14 digits. */

    accum_13 = 11 - (accum_13 % 11); /* Calculate the 13th digit. */
    if (accum_13 >= 10) accum_13 = 0;
    if (accum_13 != digit_13) return -1;
    
    accum_14 += accum_13 * 2;
    accum_14 = 11 - (accum_14 % 11); /* Calculate the 14th digit. */
    if (accum_14 >= 10) accum_14 = 0;
    if (accum_14 != digit_14) return -1;
    
    return 0;
}

#undef _CPF_CNPJ_ISDIGIT
#undef _CPF_CNPJ_ATOI

#undef CPF_CNPJ_IMPLEMENTATION
#endif /* defined(CPF_CNPJ_IMPLEMENTATION) */
