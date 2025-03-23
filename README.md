# cpf_cnpj.h

A simple Brazilian **CPF/CNPJ** validator library for **C89**.

## Usage

1. **Copy** `cpf_cnpj.h` into your project.
2. **Include** `cpf_cnpj.h` where you want to use it.
3. In **one** source file, **define** `CPF_CNPJ_IMPLEMENTATION` **before** including the header.
4. Use the `cpf_check` and `cnpj_check` **functions** as needed.

## Example

- See [example.c](./example.c) for a simple example.
- See [cpfnpj.c](./cpfnpj.c) for a usage example.

## Features

- Function `cpf_check` for validating CPFs (Brazilian individual taxpayer registry).
- Function `cnpj_check` for validating CNPJs (Brazilian corporate taxpayer registry).
- Full **C89** compliance.
- Ignores all non-numeric characters.
- Lightweight, single-header library.

# cpfnpj

A simple command-line utility for validating Brazilian **CPF/CNPJ** numbers, written in **C**.

## Usage

```sh
./build_cpfnpj.sh   # Build the program.
```

The **cpfnpj** program returns: `0` if the CPF/CNPJ is **valid**, `1` otherwise. 
Additionally, `true\n` or `false\n` is printed to `stdout`, unless the `--quiet` or `-q` flag is provided.

```sh
./cpfnpj --help | -h | -?     # Show help.
./cpfnpj <CPF> | <CNPJ>       # Check CPF or CNPJ.
./cpfnpj --cpf | -f <CPF>     # Check CPF.
./cpfnpj --cnpj | -j <CNPJ>   # Check CNPJ.
./cpfnpj -jq <CNPJ>           # Check CNPJ, quietly.
```
