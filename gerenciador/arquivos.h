/**
	\mainpage
	\author Caroline de Oliveira Braga
	\version 1.0
	\date 2020
*/

#ifndef ARQUIVOS_H_INCLUDED
#define ARQUIVOS_H_INCLUDED
#define TAM_BLOCO 200 /*!< Define o tamanho do bloco como 200 */
#define TAM_MEMORIA 100 /*!< Define o tamanho da memória como 100 */

/**
 *  Struct que representa a memória e armazena os blocos de texto
 */
typedef struct Node {
	/*@{*/
    char texto[TAM_BLOCO]; /**< Bloco de texto alocado na memória */
    /*@}*/
} node;

node memoria[TAM_MEMORIA]; /*!< Vetor de structs do tipo node */

int pos; /*!< Guarda a posição do vetor memória */
int total_blocos; /*!< Armazena a quantidade total de blocos utilizados do sistema */

/**
 * Lista encadeada onde cada nó representa os dados de um arquivo
 */
typedef struct Cadastro {
	/*@{*/
    char nome[200]; /**< Nome do arquivo */
    int inicio; /**< Primeira posição ocupada pelo arquivo na memória */
    int qtd_blocos; /**< Quantidade de blocos de memória ocupada pelo arquivo */
    int posicoes[100]; /**< Posições da memória onde estão localizados os blocos correspondentes ao arquivo */
    struct Cadastro * prox; /**< Ponteiro para o próximo elemento */
    /*@}*/
} cadastro;

FILE* arq; /*!< Arquivo aberto para ser inserido no sistema */

/*!
 * Armazena o texto de um arquivo nos blocos de memória do gerenciador
 * e acrescenta as informações desse arquivo no sistema.
 * @param cabeca2 Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * @param nome_arq Nome do arquivo a ser inserido no sistema
 * \return 1 em caso de erro, ou seja, quando arquivo é nulo
 */
int cadastrar (cadastro ** cabeca2, char * nome_arq);

/*!
 * Remove as informações de um arquivo do sistema, ou seja, da lista encadeada de informações dos arquivos (cadastro).
 * @param cabeca3 Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * @param nome_arq Nome do arquivo a ser removido do sistema
  * \return Sem retorno
 */
void descadrastrar (char nome_arq[], cadastro ** cabeca3);

/*!
 * Procura o nome de um arquivo e as informações a ele associadas no sistema, ou seja, na lista encadeada de informações (cadastro). 
 * Também imprime no terminal as informações de todos os arquivos armazenados e a lista encadeada associada ao arquivo escolhido pelo usuário.
 * @param cabeca4 Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * @param arquivo Nome do arquivo a ser buscado no sistema
 * @param flag Se flag = 1 a função exibirá na tela os resultados da busca, caso contrário, só realizará a busca
 * \return Quantidade de blocos ocupada pelo arquivo buscado no sistema
 */
int busca (cadastro * cabeca4, char * arquivo, int flag);

/*!
 * Insere um bloco de texto em uma posição do vetor memória.
 * @param bloco Bloco de texto com até 200 caracteres que será inserido
 * \return Sem retorno
 */
void inserir (char * bloco);

/*!
 * Remove o texto de um arquivo do vetor memória.
 * @param cabeca5 Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * @param arquivo Nome do arquivo a ser removido do sistema
 * \return Sem retorno
 */
void remover (cadastro * cabeca5, char * arquivo);

/*!
 * Conta as ocorrências de um termo num bloco de texto
 * @param bloco Bloco onde será buscado o termo
 * @param termo Termo que será buscado no bloco
 * \return Ocorrências do termo no bloco
 */
int contador_ocorrencias (char * bloco, char * termo);

/*!
 * Verifica se há ocorrência do termo na interseção entre dois blocos.
 * @param bloco1 Bloco onde será buscado o termo
 * @param bloco2 Bloco onde será buscado o termo
 * @param termo Termo que será buscado no bloco
 * \return Se o termo se encontra ou não na interseção dos blocos
 */
int ocorrencias_tratadas (char * bloco1, char * bloco2, char * termo);

/*!
 * Conta as ocorrências do termo no arquivo.
 * @param cabeca Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * @param termo Termo que será buscado no arquivo
 * @param nome_arq Nome do arquivo a ser inserido no sistema
 * \return Ocorrências do termo no arquivo
 */
int ocorrencias_arquivo (cadastro * cabeca, char * termo, char * nome_arq);

/*!
 * Menu onde ocorre a interação com o usuário e seleção de operações.
 * @param cad_cabeca Nó cabeça da lista encadeada de informações dos arquivos (cadastro)
 * \return Sem retorno
 */
int menu (cadastro * cad_cabeca);

#endif