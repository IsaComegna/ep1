#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

main() {

  printf("Hello World\n");
}


double* criarVetorDinamico(int N) {
    double *Vetor;

    Vetor = (double*) calloc(N, sizeof(double));

    return Vetor;
}


void destruirVetor(double* Vetor) {

    free(Vetor);
}


double** criarMatrizDinamica(int m, int n) {
    double **matriz;
    int i;
    if (m < 1 || n < 1) { /* verifica parametros recebidos */
        printf ("** Erro: Parametro invalido **\n");
        return (NULL);
    }

    /* aloca as linhas da matriz */
    matriz = (double **) calloc (m, sizeof(double *));
    if (matriz == NULL) {
        printf ("** Erro: Memoria Insuficiente **");
        return (NULL);
    }
    /* aloca as colunas da matriz */
    for (i = 0; i < m; i++) {
        matriz[i] = (double*) calloc (n, sizeof(double));
        if (matriz[i] == NULL) {
            printf ("** Erro: Memoria Insuficiente **");
            return (NULL);
        }
    }
    return matriz;
}



void destruirMatriz(double** Matriz, int linhas) {
    /* Desaloca espaco na memoria antes de fechar o programa.
    *  Sem isso, a memória RAM alocada no programa fica
    *  ocupada até o reinicio do sistema.
    *  Fonte: https://stackoverflow.com/questions/1824363/dynamic-allocation-deallocation-of-2d-3d-arrays
    */

    int i;

    for(i = 0;i < linhas; i++) {
        free(Matriz[i]);
    }

    free(Matriz);
}


/* ------------------------------- Leitura de arquivos ------------------------------- */

    double* lerVetor(char *nomeArquivo, int N) {
    double* vetor;
    double elemento;
    int i = 0;
    char linha[64];

    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("\nArquivo nao encontrado\n");
        exit(EXIT_FAILURE);
    }

    vetor = criarVetorDinamico(N);

    while(fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%le\n", &elemento);
        vetor[i] = elemento;
        i++;
    }

    fclose(arquivo);
    return vetor;
}


double** lerMatriz(char *nomeArquivo, int *linhas, int *colunas, int *nao_nulos) {
    char linha[512];
    double elemento;
    double** matriz;
    int i, j;
    int L, C, int_nao_nulos;

    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL) {
        printf("\nArquivo nao encontrado\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d %d %d\n", &L, &C, &int_nao_nulos);

    *linhas = L;
    *colunas = C;
    *nao_nulos = int_nao_nulos;

    matriz = criarMatrizDinamica(L, C);

    while(fgets(linha, sizeof(linha), arquivo) != NULL) { /* pega uma linha de até 512 caracteres. Null quando acabar as linhas */
        sscanf(linha, "%d %d   %le", &i, &j, &elemento);
        matriz[i][j] = elemento;
        /*if(i == (L - 1) && j == (C - 1)) {
            break;
        }*/
    }

    fclose(arquivo);
    return matriz;
}

//derivada em função do angulo tetaj
void derivadaTetaBarraJ(){

    for (it ; it<=k  it++){


    }
}

Pespj = 0;
Qespj = 0;
