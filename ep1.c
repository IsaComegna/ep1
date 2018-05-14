#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int main() {

/*PROTOTIPOS DAS FUNCOES*/
double** criarMatrizDinamica(int m, int n);
void destruirMatriz(double** Matriz, int linhas);
double** lerMatrizDadosBarras(char *nomeArquivo, int *linhas, int *colunas, int *nao_nulos, int opcao);
/* fim dos prototipos */

int linhas = 77;
int colunas = 6;
int nao_nulos = 310 ;

/*lendo os arquivos txt disponibilizados e criando as respectivas matrizes*/
char *stevenson_ynodal = "../EP1/1_Stevenson/1_Stevenson_Ynodal.txt";
char *stevenson_dadosbarra = "../EP1/1_Stevenson/1_Stevenson_DadosBarras.txt";
double matriz_stevenson_dados_barra = **lerMatrizDadosBarras(stevenson_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
double matriz_stevenson_ynodal = **lerMatrizDadosBarras(stevenson_ynodal, &linhas, &colunas, &nao_nulos, 1);

char *reticulada_ynodal = "../EP1/2_Reticulada/2_Reticulada_Ynodal.txt";
char *reticulada_dadosbarra = "../EP1/2_Reticulada/2_Reticulada_DadosBarras.txt";
double matriz_reticulada_dados_barra = **lerMatrizDadosBarras(reticulada_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
double matriz_reticulada_ynodal = **lerMatrizDadosBarras(reticulada_ynodal, &linhas, &colunas, &nao_nulos, 1);

char *distrib_primaria_ynodal = "../EP1/3_Distribuicao_Primaria/3_Distribuicao_Primaria_Ynodal.txt";
char *distrib_primaria_dadosbarra = "../EP1/3_Distribuicao_Primaria/3_Distribuicao_Primaria_DadosBarras.txt";
double matriz_distrib_primaria_dados_barra = **lerMatrizDadosBarras(distrib_primaria_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
double matriz_distrib_primaria_ynodal = **lerMatrizDadosBarras(distrib_primaria_ynodal, &linhas, &colunas, &nao_nulos, 1);

char *distrib_pri_sec_ynodal = "../EP1/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_Ynodal.txt";
char *distrib_pri_sec_dadosbarra = "../EP1/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_DadosBarras.txt";
double matriz_distrib_pri_sec_dados_barra = **lerMatrizDadosBarras(distrib_pri_sec_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
double matriz_distrib_pri_sec_ynodal = **lerMatrizDadosBarras(distrib_pri_sec_ynodal, &linhas, &colunas, &nao_nulos, 1);



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

double** lerMatrizDadosBarras(char *nomeArquivo, int *linhas, int *colunas, int *nao_nulos, int opcao) {
    char linha[512];
    double elemento1;
    double elemento2;
    double elemento3;
    double elemento4;

    //se opçao = 0 , o arquivo a ser lido é do tipo MatrizDadosBarras
    //se opção = 1, o arquivo a ser lido é do tipo Ynodal

    double** matriz;
    int i, j;
    int L, C;

    if (opcao == 0){
        C=5;
    } else {
        C=4;
    }
    FILE *arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL) {
        printf("\nArquivo nao encontrado\n");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d\n", &L);
    *linhas = L;
    *colunas = C;
    matriz = criarMatrizDinamica(L, C);
    while(fgets(linha, sizeof(linha), arquivo) != NULL) { /* pega uma linha de até 512 caracteres. Null quando acabar as linhas */

        if (opcao ==0){ //matriz dos dados da barra
            sscanf(linha, "%d %le %le %le %le", &i, &elemento1, &elemento2, &elemento3, &elemento4);
            matriz[i][0] = elemento1;
            matriz[i][1] = elemento2;
            matriz[i][2] = elemento3;
            matriz[i][3] = elemento4;
        } else { //matriz das admitancias Ynodal
            sscanf(linha, "%d %le %le %le", &i, &elemento1, &elemento2, &elemento3);
            matriz[i][0] = elemento1;
            matriz[i][1] = elemento2;
            matriz[i][2] = elemento3;
        }
    }
    fclose(arquivo);
    return matriz;
}
