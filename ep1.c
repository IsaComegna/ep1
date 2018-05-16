#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* variaveis globais */
int size_rows;
int size_stevenson_ynodal, size_stevenson_dadosbarra;
int size_reticulada_ynodal, size_reticulada_dadosbarra;
int size_primario_ynodal, size_primario_dadosbarra;
int size_pri_sec_ynodal, size_pri_sec_dadosbarra;

int main() {

    /*PROTOTIPOS DAS FUNCOES*/
    double** criarMatrizDinamica(int m, int n);
    void destruirMatriz(double** Matriz, int linhas);
    double** lerMatrizDadosBarras(char *nomeArquivo, int *linhas, int *colunas, int *nao_nulos, int opcao);
    void destruirVetor(int* Vetor);
    int* criarVetorDinamicoInt(int N) ;
    double* criarVetorDinamicoDouble(double N) ;
    double fpPQ(int size_ynodal, int size_dadosbarra, double** matrix_ynodal, double** matrix_dadosbarra);
    double** decomposicao_LU(double** matriz, int n, int p[]) ;
    double** obter_matriz_L(double** matriz, int n);
    double** obter_matriz_U(double** matriz, int n);
    double** resolucao_sistema_linear(double** A, double* b, int n);
    /* fim dos prototipos */

    int linhas = 77;
    int colunas = 6;
    int nao_nulos = 310 ;

    /*lendo os arquivos txt disponibilizados e criando as respectivas matrizes*/

    char *stevenson_ynodal = "../EP1/1_Stevenson/1_Stevenson_Ynodal.txt";
    char *stevenson_dadosbarra = "../EP1/1_Stevenson/1_Stevenson_DadosBarras.txt";
    double** matriz_stevenson_dados_barra = lerMatrizDadosBarras(stevenson_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
    size_stevenson_dadosbarra = size_rows;
    double** matriz_stevenson_ynodal = lerMatrizDadosBarras(stevenson_ynodal, &linhas, &colunas, &nao_nulos, 1);
    size_stevenson_ynodal = size_rows;

    char *reticulada_ynodal = "../EP1/2_Reticulada/2_Reticulada_Ynodal.txt";
    char *reticulada_dadosbarra = "../EP1/2_Reticulada/2_Reticulada_DadosBarras.txt";
    double** matriz_reticulada_dados_barra = lerMatrizDadosBarras(reticulada_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
    size_reticulada_dadosbarra = size_rows;
    double** matriz_reticulada_ynodal = lerMatrizDadosBarras(reticulada_ynodal, &linhas, &colunas, &nao_nulos, 1);
    size_reticulada_ynodal = size_rows;

    char *distrib_primaria_ynodal = "../EP1/3_Distribuicao_Primaria/3_Distribuicao_Primaria_Ynodal.txt";
    char *distrib_primaria_dadosbarra = "../EP1/3_Distribuicao_Primaria/3_Distribuicao_Primaria_DadosBarras.txt";
    double** matriz_distrib_primaria_dados_barra = lerMatrizDadosBarras(distrib_primaria_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
    size_primario_dadosbarra = size_rows;
    double** matriz_distrib_primaria_ynodal = lerMatrizDadosBarras(distrib_primaria_ynodal, &linhas, &colunas, &nao_nulos, 1);
    size_primario_ynodal = size_rows;

    char *distrib_pri_sec_ynodal = "../EP1/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_Ynodal.txt";
    char *distrib_pri_sec_dadosbarra = "../EP1/4_Distribuicao_Pri_Sec/4_Distribuicao_Primaria_Secundaria_DadosBarras.txt";
    double** matriz_distrib_pri_sec_dados_barra = lerMatrizDadosBarras(distrib_pri_sec_dadosbarra, &linhas, &colunas , &nao_nulos, 0);
    size_pri_sec_dadosbarra = size_rows;
    double** matriz_distrib_pri_sec_ynodal = lerMatrizDadosBarras(distrib_pri_sec_ynodal, &linhas, &colunas, &nao_nulos, 1);
    size_pri_sec_ynodal = size_rows;

    double** A = criarMatrizDinamica(3,3);

    A[0][0] = 5;
    A[0][1] =2;
    A[0][2]=1;
    A[1][0] =3;
    A[1][1] =1;
    A[1][2]=4;
    A[2][0] =1;
    A[2][1] =1;
    A[2][2]=3;

    double* b = criarVetorDinamicoDouble(3);
    b[0]=0;
    b[1] = -7;
    b[2] = -5;


    /*double** L = obter_matriz_L(LU, 3);
    double** U = obter_matriz_U(LU, 3);*/
    double** blebs = resolucao_sistema_linear(A, b, 3);

};

double Pcalc(int size_ynodal, int size_dadosbarra, double** matrix_ynodal, double** matrix_dadosbarra) {

    double somatorio = 0;
    double calculo;

    for (int j=0; j<=size_dadosbarra; j++){
        for (int k=0; k<= size_ynodal; k++ ){
            calculo = matrix_dadosbarra[j][0];
            somatorio = somatorio + calculo;
        };
    };
    return calculo;
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
    size_rows = L;
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

int* criarVetorDinamicoInt(int N) {
    int *Vetor;

    Vetor = (int*) calloc(N, sizeof(int));

    return Vetor;
}

double* criarVetorDinamicoDouble(double N) {
    double *Vetor;

    Vetor = (double*) calloc(N, sizeof(double));

    return Vetor;
}


void destruirVetor(int* Vetor) {

    free(Vetor);
}


double** decomposicao_LU(double** matriz, int n, int p[]) {
    //matriz nxn
    double** a = criarMatrizDinamica(n, n);

    for (int k=0; k<n; k++){ //cria copia da matriz que a função recebe na matriz a
        for (int i=0; i<n; i++ ){
            a[k][i] = matriz[k][i];
        }
    };

    double somatorio;
    double pivo;
    int l;
    double aux;
    int troca;
    double m;
    for (int k=0; k<n; k++){
        pivo = abs(a[k][k]);
        l = k;
        for (int i=k+1; i<n; i++ ){ //calculo de a(i,k)
            if (abs(a[i][k]) > pivo){
                pivo= a[i][k];
                l=i;
            }
        }
        if (l != k){ //troca de linhas da matriz (linha p(k) e linha k)
            troca = p[k];
            p[k] = p[l];
            p[l] = troca;

            for(int j=0; j<n; j++){
                aux = a[k][j];
                a[k][j] = a[l][j];
                a[l][j] = aux;
            }
        }
        for (int i=k+1; i<n; i++){

            m = a[i][k]/a[k][k];
            a[i][k] = m;

            for (int j=k+1 ; j<n; j++){
                a[i][j] =a[i][j] - m*a[k][j];
            }
        }
    }
/*
    printf("%le \n", a[0][0]);
    printf("%le \n", a[0][1]);
    printf("%le \n", a[0][2]);
    printf("%le \n", a[1][0]);
    printf("%le \n", a[1][1]);
    printf("%le \n", a[1][2]);
    printf("%le \n", a[2][0]);
    printf("%le \n", a[2][1]);
    printf("%le \n", a[2][2]);*/

return a;
}


double** obter_matriz_L(double** matriz, int n) {
    //matriz nxn
    double** L = criarMatrizDinamica(n, n);
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++ ){
            if(k==i){
                L[k][i] = 1;
            }
            if(k > i){
                L[k][i] = matriz[k][i];
            }
        }
    };
    return L;
}


double** obter_matriz_U(double** matriz, int n) {
    //matriz nxn
    double** U = criarMatrizDinamica(n, n);
    for (int k=0; k<n; k++){
        for (int i=0; i<n; i++ ){
            if(k <= i){
                U[k][i] = matriz[k][i];
            }
        }
    };
    return U;
}


double** resolucao_sistema_linear(double** A, double* b, int n) {
    //matriz A nxn
    /*  Quero resolver o sistema Ax = b
        tenho que c = Pb, sendo P o vetor das permutacoes na decomposicao LU
        Ly=Pb
        Ux=y
    */

    int* p = criarVetorDinamicoInt(3); //vetor de permutacoes
    for(int i=0; i<3 ; i++){
        p[i] = i;
    }
    double** LU = decomposicao_LU(A, n, p);
    double** L = obter_matriz_L(LU, n);
    double** U = obter_matriz_U(LU, n);


    double* c = criarVetorDinamicoDouble(n); //vetor de permutacoesdouble** a = criarMatrizDinamica(n, n);
    double* y = criarVetorDinamicoDouble(n);
    double* x = criarVetorDinamicoDouble(n);

    int aux;

    for (int i=0; i<n; i++){ //c=Pb
        aux = p[i];
        c[i] = b[aux];
    }

    double s;
    for(int i=0; i<n; i++){ //Ly = Pb
        s=0;
        for(int j=0; j<n-1; j++){
            s = s + L[i][j]*y[j];
        }
        y[i] = (c[i] - s)/L[i][i];
    };

    /*printf("%le \n", y[0]);
    printf("%le \n", y[1]);
    printf("%le \n", y[2]);*/

/*
    for(int i=n; i>0; i--){ //Ux=y
        s=0;
        for(int j=i; j<n; j++){
            s = s + U[i][j]*x[j];
        }
        x[i] = (y[i] - s)/U[i][i];
    }*/

/*
    printf("%le \n", x[0]);
    printf("%le \n", x[1]);
    printf("%le \n", x[2]);*/

    return x;

}
