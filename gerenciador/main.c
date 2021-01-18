#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"

int main (int argc, char *argv[]){
    int blocos;
    pos = 0, total_blocos = 0;

    cadastro * cabeca = NULL;
    cabeca = (cadastro *) malloc(sizeof(cadastro));
    cabeca -> prox = NULL;

    for (int i = 1; i < argc; i++) {
        if (total_blocos == TAM_MEMORIA){
            printf("Erro! Memoria cheia.\n");
            break;
        }
        cadastrar (&cabeca, argv[i]);
    }

    menu (cabeca);

    return 0;
}