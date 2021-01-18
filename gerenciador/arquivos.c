#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"

void descadrastrar(char nome_arq[], cadastro ** cabeca3){
    cadastro * temp = NULL;
    cadastro * anterior = NULL;
    cadastro * atual = *cabeca3;
    if(NULL == atual){
        printf("Erro! Nenhum arquivo cadastrado.\n");
        return;
    }
    if (0 == strcmp (nome_arq, atual -> nome)) {
        temp = atual;
        *cabeca3 = atual -> prox;
        free(temp);
    }
    else {
        while(NULL != atual && 0 != strcmp (nome_arq, atual -> nome)){
            anterior = atual;
            atual = atual -> prox;   
        }
        if (NULL != atual) {
            temp = atual;
            anterior -> prox = atual -> prox;
            free(temp);
        }
    }   
}

int busca (cadastro * cabeca4, char * arquivo, int flag) {
    cadastro * atual = cabeca4;
    while (atual -> prox != NULL) {
    	if (flag == 1) {
    		printf("nome: %s | inicio: %d | blocos: %d\n", atual -> nome, atual -> inicio, atual -> qtd_blocos);
    	}
        if (strcmp(arquivo, atual -> nome) == 0){
            if (flag == 1) {
            	printf("O arquivo %s esta nas seguintes posicoes da memoria:\n", atual -> nome);
            	for (int i = 0; i < atual -> qtd_blocos; i++){
            		printf ("%d ", atual -> posicoes[i]);
            	}
            	printf("\n");
            }
            return atual -> qtd_blocos;
        }
        atual = atual -> prox;
    }
    printf ("Arquivo nao encontrado.\n");
}

void inserir (char * bloco) {
    while (*memoria[pos].texto != '\0') {
        pos++;
    }
    strcpy (memoria[pos].texto, bloco);
}

void remover (cadastro * cabeca5, char * arquivo) {
	int blocos = busca (cabeca5, arquivo, 0);
	for (int i = 0; i < blocos; i++) {
		*memoria[cabeca5 -> posicoes[i]].texto == '\0';
	}
	total_blocos -= blocos;
}

int cadastrar (cadastro ** cabeca2, char * nome_arq) {
	int blocos = 0, j = 0, faltam = 0;
	char bloco[TAM_BLOCO];

	arq = fopen (nome_arq, "rb");
	if (arq == NULL) {
    	printf("Erro! Tente novamente.\n");
    	return 1;
    }

    cadastro * novo_node;
    novo_node = (cadastro *) malloc(sizeof(cadastro));
    strcpy (novo_node -> nome, nome_arq);
    
    while (fread(bloco, TAM_BLOCO, 1, arq) != 0) {
    	inserir (bloco);
    	if (j == 0)
    		novo_node -> inicio = pos;
    	novo_node -> posicoes[j] = pos;
    	blocos++;
    	j++;
    }

    fseek(arq, 0, SEEK_END);
    faltam = ftell(arq) - TAM_BLOCO * blocos;

    if (faltam != 0){
    	fread(bloco, faltam, 1, arq);
    	inserir (bloco);
    	novo_node -> posicoes[j] = pos;
    	blocos++;
    }

    fclose (arq);
    total_blocos += blocos;

    novo_node -> qtd_blocos = blocos;
    novo_node -> prox = *cabeca2;
    *cabeca2 = novo_node;
}

int contador_ocorrencias (char * bloco, char * termo) {
    int i, j, flag, qtd = 0;
    int tam_termo = strlen(termo);
    for ( i = 0; i <= TAM_BLOCO - tam_termo; i++) {
        flag = 1;
        for (j = 0; j < tam_termo; j++) {
            if (bloco[i + j] != termo[j]) {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            qtd++;
    }
    return qtd;
}

int ocorrencias_tratadas (char * bloco1, char * bloco2, char * termo) {
    int tam = strlen (bloco1);
    char * ptr, b1[tam];
    ptr = strtok (bloco1," ,.-");
    while (ptr != NULL) {
        strcpy (b1, ptr);
        ptr = strtok (NULL, " ,.-");
    }
    ptr = strtok (bloco2, " ,.-");
    int tam_temp = strlen (b1) + strlen (bloco2);
    char temp[tam_temp];
    strcpy (temp, b1);
    strcat (temp, bloco2);
    if (strstr (temp, termo) == NULL)
        return 0;
    else
        return 1;
}

int ocorrencias_arquivo (cadastro * cabeca6, char * termo, char * nome_arq) {
    int qtd_bloco = 0, qtd_tratada = 0, blocos = busca (cabeca6, nome_arq, 0);
	for (int i = 0; i < blocos; i++) {
		qtd_bloco += contador_ocorrencias (memoria[cabeca6 -> posicoes[i]].texto, termo);
		if (i != blocos - 1)
        	qtd_tratada += ocorrencias_tratadas (memoria[cabeca6 -> posicoes[i]].texto, memoria[cabeca6 -> posicoes[i+1]].texto, termo);
	}
    return qtd_bloco + qtd_tratada;
}

int menu (cadastro * cad_cabeca) {
    int operacao, blocos, qtd_arquivo;
    char arquivo[200], termo[100];
    while (1) {
        printf("Qual operacao deseja realizar?\n");
        printf("1 - Insercao\n2 - Remocao\n3 - Busca de arquivo\n4 - Busca de termo\n5 - Nenhuma/sair do programa\n");
        scanf ("%d", &operacao);

        switch (operacao) {
            case 1:
                if (total_blocos == TAM_MEMORIA){
                  printf("Erro! Memoria cheia.\n");
                  break;
                }
                printf ("Digite o nome do arquivo que deseja inserir:\n");
                scanf ("%s", arquivo);
                cadastrar (&cad_cabeca, arquivo);
                break;
            case 2:
                printf ("Digite o nome do arquivo que deseja remover:\n");
                scanf ("%s", arquivo);
                remover (cad_cabeca, arquivo);
                descadrastrar (arquivo, &cad_cabeca);
                break;
            case 3:
                printf ("Digite o nome do arquivo que deseja buscar:\n");
                scanf ("%s", arquivo);
                busca (cad_cabeca, arquivo, 1);
                break;
            case 4:
                printf ("Digite o termo que deseja buscar:\n");
                scanf ("%s", termo);
				cadastro * atual = cad_cabeca;
				while (atual -> prox != NULL) {
					qtd_arquivo = ocorrencias_arquivo (atual, termo, atual -> nome);
					printf("arquivo = %s | ocorrencias = %d\n", atual -> nome, qtd_arquivo);
				    atual = atual -> prox;
                    qtd_arquivo = 0;
				}
                break;
            case 5:
                return 0;
            default:
                return 0;
        }
    }
}