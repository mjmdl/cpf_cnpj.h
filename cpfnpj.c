#include <stdio.h>
#include <string.h>

#define CPF_CNPJ_IMPLEMENTATION
#include "cpf_cnpj.h"

#define FLAG_CPF   (1 << 0)
#define FLAG_CNPJ  (1 << 1)
#define FLAG_QUIET (1 << 2)

static void
print_usage (char const *prog)
{
    printf("USAGE: %s [--quiet] [<cpf> | <cnpj>] | [--cpf <cpf>] | [--cnpj <cnpj>]\n", prog);
}

static void
print_help (char const *prog)
{
    print_usage(prog);
    printf("INFO: Validates the provided CPF or CNPJ.\n");
    printf("      Returns 0 if valid, 1 otherwise.\n");
    printf("      Prints 'true' or 'false' to stdout unless --quiet is used.\n");
    printf("      -f, --cpf      validate CPF\n");
    printf("      -j, --cnpj     validate CNPJ\n");
    printf("      -q, --quiet    suppress stdout output\n");
}

int
main (int argc, char **argv)
{
    int flags;
    char const *input, *prog, *arg, *ptr;

    flags = 0, input = NULL, prog = argv[0];

    for (int i = 1; i < argc; ++i) {
        arg = argv[i];
        if (arg[0] == '-') {
            if ((arg[1] == 'h') || (arg[1] == '?') || (strcmp(arg, "--help") == 0)) {
                print_help(prog);
                return 0;
            }
            else if (strcmp(arg, "--quiet") == 0) flags |= FLAG_QUIET;
            else if (strcmp(arg, "--cpf")   == 0) flags |= FLAG_CPF;
            else if (strcmp(arg, "--cnpj")  == 0) flags |= FLAG_CNPJ;
            else {
                for (ptr = &arg[1]; *ptr != '\0'; ++ptr) {
                    if      (*ptr == 'q') flags |= FLAG_QUIET;
                    else if (*ptr == 'f') flags |= FLAG_CPF;
                    else if (*ptr == 'j') flags |= FLAG_CNPJ;
                    else                  break;
                }
                if (*ptr != '\0') {
                    fprintf(stderr, "ERROR: Unknown argument is provided: %s\n", arg);
                    print_usage(prog);
                    return 1;
                }
            }
        } else {
            if (input != NULL) {
                fprintf(stderr, "ERROR: Input argument provided more than once.\n");
                print_usage(prog);
                return 1;
            }
            input = argv[i];
        }
    }

    if (input == NULL) {
        fprintf(stderr, "ERROR: Input value is not provided.\n");
        print_usage(prog);
        return 1;
    }
    if (!(flags & (FLAG_CPF | FLAG_CNPJ))) flags |= FLAG_CPF | FLAG_CNPJ;
    
    if ((flags & FLAG_CPF) && (cpf_check(input) == 0)) {
        if (!(flags & FLAG_QUIET)) printf("true\n");
        return 0;
    }

    if ((flags & FLAG_CNPJ) && (cnpj_check(input) == 0)) {
        if (!(flags & FLAG_QUIET)) printf("true\n");
        return 0;
    }

    if (!(flags & FLAG_QUIET)) printf("false\n");
    return 1;
}
