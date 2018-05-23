#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

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
	int* criarVetorDinamicoInt(int N);
	double* criarVetorDinamicoDouble(double N);
	void imprimirVetor(double* v, int n);
	void imprimirMatriz(double** A, int linhas, int colunas);
	double fpPQ(int size_ynodal, int size_dadosbarra, double** matrix_ynodal, double** matrix_dadosbarra);
	double** decomposicao_LU(double** matriz, int n, int p[]) ;
	double** obter_matriz_L(double** matriz, int n);
	double** obter_matriz_U(double** matriz, int n);
	double* resolucao_sistema_linear(double** A, double* b, int n);
	double* metodo_de_newton_teste(double* x0, int n, double E, int teste);
	double** calcularJacobianaTeste1(double* x);
	double** calcularJacobianaTeste2(double* x);
	double*  calcularFuncaoTeste1(double* x);
	double*  calcularFuncaoTeste2(double* x);
	double* metodo_de_newton_stevenson(double* teta, double* V, int nPQ, int nPV, double** matriz_admitancias);

	/* fim dos prototipos */

	int linhas = 77;
	int colunas = 6;
	int nao_nulos = 310;

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


//--------TESTE 1--------------------------------------------------------------
	/*printf("Rodando Teste 1...\n");
	double* x1 = criarVetorDinamicoDouble(2);
	x1[0] = 1;
	x1[1] = 5;

	// double* teste1 = metodo_de_newton_teste(x1, 2, 0.00001, 1);

	// printf("Resultado Teste 1:\n");
	// imprimirVetor(teste1, 2);

//-----------------------------------------------------------------------TESTE 2
	/*double* x = criarVetorDinamicoDouble(4);
	x[0] = 1;
	x[1] = 1;
	x[2] = 1;
	x[3] = 1;

//--------TESTE 3---------------------------------------------------------------
	// printf("Rodando Teste 3...\n");
	// int N = 7;
	//double* teste2 = metodo_de_newton2(x, 4, 0.1);

/*
	printf("Resultado Teste 2:\n");
	printf("%le \n", teste2[0]);
	printf("%le \n", teste2[1]);
	printf("%le \n", teste2[2]);
	printf("%le \n", teste2[3]);*/

	// /*Criando vetor unitário*/
	// for(int i=0; i<N; i++){
	//     x3[i] = 1;
	// }
	// // double wait = 2 - ( exp(x3[2]) / (N*N) );
	// // printf("wait = %le\n", wait);
	// double* teste3 = metodo_de_newton_teste(x3, N, 0.1, 3);

	// printf("Resultado Teste 3:\n");
	// imprimirVetor(teste3, N); */


//    double* fp = calculo_fp(x, x, 1, 1, Jx);


	/*------------- Calculo rede 1: Stevenson -----------*/
	/* a rede tem 5 barras, de 0 a 4
	   uma barra do tipo swing
	   3 barras do tipo PQ e 1 barra do tipo PV */
	double* teta = criarVetorDinamicoDouble(5);
	double* V = criarVetorDinamicoDouble(5);
	for (int i=0; i<5; i++){
		V[i] = 132790.562;
	}
	int nPQ = 3; //existem 3 barras PQ na rede
	int nPV = 1; //existe 1 uma barra PV na rede
	double* x_st = metodo_de_newton_stevenson(teta, V, nPQ, nPV, matriz_stevenson_ynodal);

	for (int i=0; i<5; i++){
		printf("%le \n", x_st[i]);
	}



	/*---------------fim to calculo rede 1-----------*/
}

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

/*cria uma matriz dinamica*/
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

/*destroi uma matriz dinamica*/
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

/*le um arquivo txt e retorna uma matriz a partir do arquivo lido, cujos elementos foram retirados do arquivo*/
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

	int iter =0;
	matriz = criarMatrizDinamica(L, C);
	while(fgets(linha, sizeof(linha), arquivo) != NULL) { /* pega uma linha de até 512 caracteres. Null quando acabar as linhas */

		if (opcao == 0){ //matriz dos dados da barra
			sscanf(linha, "%d %d %le %le %le", &i, &j, &elemento2, &elemento3, &elemento4);
			matriz[iter][0] = i;
			matriz[iter][1] = j;
			matriz[iter][2] = elemento2;
			matriz[iter][3] = elemento3;
			matriz[iter][4] = elemento4;
		}
		if (opcao ==1) { //matriz das admitancias Ynodal
			sscanf(linha, "%d %d %le %le", &i, &j, &elemento1, &elemento2);
			matriz[iter][0] = i;
			matriz[iter][1] = j;
			matriz[iter][2] = elemento1;
			matriz[iter][3] = elemento2;
		}
		iter++;
	}
	fclose(arquivo);
	return matriz;
}

/*cria um vetor de numeros inteiros*/
int* criarVetorDinamicoInt(int N) {
	int *Vetor;

	Vetor = (int*) calloc(N, sizeof(int));

	return Vetor;
}

/*cria um vetor de numeros fracionarios*/
double* criarVetorDinamicoDouble(double N) {
	double *Vetor;

	Vetor = (double*) calloc(N, sizeof(double));

	return Vetor;
}

/*destroi um vetor de inteiros*/
void destruirVetor(int* Vetor) {
	free(Vetor);
}

void imprimirVetor(double* v, int n){
	for(int i=0; i<n; i++){
		if(v[i]>=0){
			printf("|  %le  |   %d\n", v[i], i);
		} else {
		printf("| %le  |   %d\n", v[i], i);
		}
	}
}


void imprimirMatriz(double** A, int linhas, int colunas){
	for(int i=0; i<linhas; i++){
		printf("| ");
		for(int j=0; j<colunas; j++){
			if(A[i][j]>=0){
				printf(" ");
			}
			printf(" %le  ", A[i][j]);
		}
		printf("  |  %d\n", i);
	}
}

/*cálculo e retorno da matriz LU a partir da decomposição de uma matriz dada*/
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
		pivo = fabs(a[k][k]);
		l = k;
		for (int i=k+1; i<n; i++ ){ //calculo de a(i,k)
			if (fabs(a[i][k]) > pivo){
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


return a;
}

/*dada a matriz LU, retorna a matriz L*/
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

/*dada a matriz LU, retorna a matriz U*/
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

/*calcula e retorna a solução de um sistema linear pelo metodo da decomposicao LU*/
double* resolucao_sistema_linear(double** A, double* b, int n) {
	//matriz A nxn

	/*  Quero resolver o sistema Ax = b
		tenho que c = Pb, sendo P o vetor das permutacoes na decomposicao LU
		Ly=Pb
		Ux=y
	*/

	int* p = criarVetorDinamicoInt(n); //vetor de permutacoes
	for(int i=0; i<n ; i++){
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

	for(int i=n-1; i>=0; i--){ //Ux=y
		s=0;
		if (i!=n-1){
			for(int j=i+1; j<n; j++){
				s = s + U[i][j]*x[j];
			}
		}
		x[i] = (y[i] - s)/(U[i][i]);
	}


	//desalocando as matrizes e vetores criados que nao serao mais utilizados
	free(y);
	free(c);
	destruirMatriz(LU, n);
	destruirMatriz(U, n);
	destruirMatriz(L, n);

	return x;
}


/* Recebe um vetor e devolve o maior módulo */
double max_valor(double* A, int n){
  double max = fabs(A[0]);
  for(int i=1; i<n; i++){
	if(fabs(A[i]) > max){ // fabs(x) = |x|
	  max = fabs(A[i]);
	}
  }
  return max;
}

/* Recebe dois vetores do mesmo tamanho e retorna a soma deles*/
double* soma_de_vetor(double* a, double* b, int n){
  double* s = criarVetorDinamicoDouble(n);
  for(int i=0; i<n; i++){
	s[i] = a[i] + b[i];
  }
  return s;
}

/* Jc=-F -> c
   novo x = x+c */


/*calcula valor da Jacobiana J(x) no teste 1*/
double** calcularJacobianaTeste1(double* x){
	/*F(x,y) = (x-2)²-(y-3)²
	o jacobiano da função será: J(x,y) = [2x-4   2y-6]*/
	double** J = criarMatrizDinamica(2,2);
	J[0][0] = 2;
	J[0][1] = 0;
	J[1][0] = 0;
	J[1][1] = 2;

	return J;

}

/*calcula valor da Jacobiana J(x) no teste 2*/
double** calcularJacobianaTeste2(double* x){
	/*F(x1,x2,x3,x4) = (f1, f2, f3, f4)
	f1 = 4x1 - x2 + x3 -x1x4
	f2 = -x1 + 3x2 - 2x3 - x2x4
	f3 = x1 - 2x2 + 3x3 - x3x4
	f4 = x1^2 + x2^2 + x3^2 - 1

	| df1/dx1   df1/dx2   df1/dx3   df1/dx4 |
	| df2/dx1   df2/dx2   df2/dx3   df2/dx4 |
	| df3/dx1   df3/dx2   df3/dx3   df3/dx4 |
	| df4/dx1   df4/dx2   df4/dx3   df4/dx4 |
	*/
	double** J = criarMatrizDinamica(4,4);

	J[0][0] = 4-x[3];
	J[0][1] = -1;
	J[0][2] = 1;
	J[0][3] = -x[0];

	J[1][0] = -1;
	J[1][1] = 3-x[3];
	J[1][2] = -2;
	J[1][3] = -x[1];

	J[2][0] = 1;
	J[2][1] = -2;
	J[2][2] = 3-x[3];
	J[2][3] = -x[2];

	J[3][0] = 2*x[0];
	J[3][1] = 2*x[1];
	J[3][2] = 2*x[2];
	J[3][3] = 0;

	return J;

}


/*calcula valor da Jacobiana J(x) no teste 3*/
/*
double** calcularJacobianaTeste3(double* x, int n){
	/*F1(x) = x[i-1] + 2x[i] - x[i+1] - e^x[i]/n^2*/
/*    double n2 = ((n+1)*(n+1));
	double** J = criarMatrizDinamica(n,n);
	J[0][0] = 2 - ( exp(x[0]) / n2 );
	J[0][1] = -1;
	for(int i=1; i<n; i++){
		J[i][i-1] = -1;
		J[i][i] = 2 - ( exp(x[i]) / n2 );
		J[i][i+1] = -1;
	}
	J[n-1][n-2] = -1;
	J[n-1][n-1] = 2 - ( exp(x[n-1]) / n2 );

	printf("Jacobiana:\n");
	imprimirMatriz(J, n, n);
	printf("Jacobiana deu bom\n");
	return J;

}*/

double*  calcularFuncaoTeste1(double* x){
	/*F(x,y) = (x-2)²-(y-3)²*/
	double* F = criarVetorDinamicoDouble(2);
	F[0] = -(2*x[0] - 4);
	F[1] = -(2*x[1] - 6);

	return F;
}

double*  calcularFuncaoTeste2(double* x){
	/*F(x1,x2,x3,x4) = (f1, f2, f3, f4)
	f1 = 4x1 - x2 + x3 -x1x4
	f2 = -x1 + 3x2 - 2x3 - x2x4
	f3 = x1 - 2x2 + 3x3 - x3x4
	f4 = x1^2 + x2^2 + x3^2 - 1*/
	double* F = criarVetorDinamicoDouble(4);
	F[0] = -(4*x[0] - x[1] + x[2] -x[0]*x[3]);
	F[1] = -(-x[0] + 3*x[1] - 2*x[2] - x[1]*x[3]);
	F[2] = -(x[0] - 2*x[1] + 3*x[2] - x[2]*x[3]);
	F[3] = -(x[0]*x[0] + x[1]*x[1] + x[2]*x[2] - 1);

	return F;
}
/*
double*  calcularFuncaoTeste3(double* x, int n){
	/*F1(x) = x[i-1] + 2x[i] - x[i+1] - e^x[i]/n^2
	x[-1]= 0 ; x[n] = 0
	*/
	/*printf("n = %d\n", n);
	double* F = criarVetorDinamicoDouble(n);
	double n2 = ((n+1)*(n+1));

	F[0] = 2*x[0] - x[1] - ( exp(x[0]) / n2 );
	for(int i = 1; i< n-1; i++){
		F[i] = -x[i-1] + 2*x[i] - x[i+1] - ( exp(x[i]) / n2 );
	}
	F[n-1] = -x[n-2] + 2*x[n-1] - ( exp(x[n-1]) / n2 );

	printf("F(x):\n");
	imprimirVetor(F, n);


	return F;
}*/

double* metodo_de_newton_teste(double* x0, int n, double E, int teste){

	double erro = 1.0;
	double* x = x0;
	int iteracoes = 1;

	double** J;
	double* F;
	double* c;

	if(teste == 1){
		while(erro > E){
			J = calcularJacobianaTeste1(x);
			F = calcularFuncaoTeste1(x);
			c = resolucao_sistema_linear(J, F, n);
			erro = max_valor(c, n);
			iteracoes++;
			x = soma_de_vetor(x, c, n);
		}
		return x;
	}

	if(teste == 2){
		while(erro > E){
			J = calcularJacobianaTeste2(x);
			F = calcularFuncaoTeste2(x);
			c = resolucao_sistema_linear(J, F, n);
			erro = max_valor(c, n);
			iteracoes++;
			x = soma_de_vetor(x, c, n);
		}
		printf("iteracoes: %d\n", iteracoes);
		return x;
	}
/*
	if(teste == 3){
		while(erro > E){
			J = calcularJacobianaTeste3(x, n);
			F = calcularFuncaoTeste3(x, n);
			c = resolucao_sistema_linear(J, F, n);
			// printf("c:\n");
			// imprimirVetor(c, n);
			erro = max_valor(c, n);
			iteracoes++;
			x = soma_de_vetor(x, c, n);
			// printf("x:\n");
			// imprimirVetor(x, n);
		}
		return x;
	}*/
}

double** criarMatrizG (int tipo, double** matriz_admitancias, int size){

	double** G = criarMatrizDinamica(size, size);

	int linha;
	int coluna;
	double elemento;
	for (int i=0; i<size; i++){
			linha = matriz_admitancias[i][0];
			coluna = matriz_admitancias[i][1];
			elemento = matriz_admitancias[i][2];
			G[linha][coluna] = elemento;
		}

	if (tipo ==0 ){

		G[0][0] =  8.30197e-003;
		G[0][1] = 0.00000e+000 ;
		G[0][2] = 0.00000e+000 ;
		G[0][3] = -3.48050e-003 ;
		G[0][4] = -2.64756e-003 ;

		G[1][0] = 0.00000e+000;
		G[1][1] =4.41207e-003;
		G[1][2] =-1.76504e-003;
		G[1][3] =-1.32378e-003 ;
		G[1][4] =0.00000e+000;

		G[2][0] = 0.00000e+000;
		G[2][1] = -1.76504e-003;
		G[2][2] = 8.98816e-003;
		G[2][3] = -2.13582e-003;
		G[2][4] = -3.48050e-003;

		G[3][0] = -3.48050e-003 ;
		G[3][1] = -1.32378e-003 ;
		G[3][2] = -2.13582e-003 ;
		G[3][3] = 8.26335e-003 ;
		G[3][4] = 0.00000e+000;

		G[4][0] = -2.64756e-003;
		G[4][1] = 0.00000e+000 ;
		G[4][2] = -3.48050e-003 ;
		G[4][3] = 0.00000e+000 ;
		G[4][04] = 7.35679e-003;
	}

	return G;
}


double** criarMatrizB (int tipo, double** matriz_admitancias, int size){

	double** B = criarMatrizDinamica(size, size);

	int linha;
	int coluna;
	double elemento;
	for (int i=0; i<size; i++){

			linha = matriz_admitancias[i][0];
			coluna = matriz_admitancias[i][1];
			elemento = matriz_admitancias[i][3];
			B[linha][coluna] = elemento;
		}

	if (tipo == 0){
		B[0][0] = -2.58029e-002 ;
		B[0][1] = 0.00000e+000 ;
		B[0][2] = 0.00000e+000 ;
		B[0][3] = 1.41465e-002 ;
		B[0][4] = 1.05902e-002;

		B[1][0] = 0.00000e+000 ;
		B[1][1] = -1.27872e-002 ;
		B[1][2] = 7.06016e-003 ;
		B[1][3] = 5.29512e-003 ;
		B[1][4] = 0.00000e+000;

		B[2][0] = 0.00000e+000 ;
		B[2][1] = 7.06016e-003 ;
		B[2][2] = -3.02904e-002 ;
		B[2][3] = 8.46267e-003 ;
		B[2][4] = 1.41465e-002;

		B[3][0] = 1.41465e-002 ;
		B[3][1] = 5.29512e-003 ;
		B[3][2] = 8.46267e-003 ;
		B[3][3] = -2.85055e-002 ;
		B[3][4] = 0.00000e+000;

		B[4][0] = 1.05902e-002 ;
		B[4][1] = 0.00000e+000 ;
		B[4][2] = 1.41465e-002 ;
		B[4][3] = 0.00000e+000 ;
		B[4][4] = -2.52358e-002;
	}

	return B;
}



double* calculo_F(double* teta, double* V, int nPQ, int nPV, double** matriz_admitancias){
	/*  teta é o vetor dos tetas, V é o vetor das tensoes
		nPQ é o numero de barras PQ
		nPV é o numero de barras PV
		nS é o numero de barras swing */

	/* --- Para Stevenson ---- */
	/* irei reorganizar a matriz ynodal e de dados das barras, para a ordem ser
		primeiro as barras pq, depois as barras pv e depois a barra swing
		ou seja, mapeio as barras como:
		[0 1 2 3 4] -> [4 0 3 1 2], ou: a barra 0 vira a barra 4,
		a barra 1 vira a barra 0 e assim por diante
		Isso é feito nas duas funçoes abaixo */

	double** G = criarMatrizG(0, matriz_admitancias, size_stevenson_dadosbarra);
	double** B = criarMatrizB(0, matriz_admitancias, size_stevenson_dadosbarra);

	double teta_kj;
	double soma;

	//F é [fp1, fp2, fp3, fp4, fq1, fq2, fq3]
	//a barra 0 é do tipo swing e nao contribui para o sistema de equações
	double* F = criarVetorDinamicoDouble(2*nPQ + nPV); //matriz F

	double Pesp = 60000000; //P esperado para o calculo da barra PV

	/* calculos de fp em F */
	for (int j=0; j<nPQ+nPV; j++){
		soma=0;
		for (int k=0; k < size_stevenson_dadosbarra; k++){ //uso todas as barras para calcular fp
				teta_kj = teta[k] - teta[j];
				soma = soma + V[k]*(G[j][k]*cos(teta_kj) - B[j][k]*sin(teta_kj));

		}
		F[j] = V[j]*soma; //+ V[k]*V[k]*G[k][k];
	}

	for(int i=0; i<nPV; i++){ //fp(j) = fp(j) - Pesp para as barras PV
		F[nPQ + i] = F[nPQ + nPV ] - Pesp; //começa na barra PV
/////////////		F[nPQ + i] = F[nPQ + nPV] - Pesp;
	}

	/* calculos de fq em F */
	for (int i=0; i<nPQ; i++){
		soma =0;
		for (int j=0; j<size_stevenson_dadosbarra; j++){ //uso todas as barras para calcular fq
			teta_kj = teta[j] - teta[i];
			soma = soma + V[j]*(G[i][j]*sin(teta_kj)+B[i][j]*cos(teta_kj));
		}
		F[nPQ+nPV+i] = -V[i]*soma;
	}

	return F;
}

double** calculo_J(double* teta, double* V, int nPQ, int nPV, double** matriz_admitancias){

	int size_barra = size_stevenson_dadosbarra; //para o caso 1 de stevenson

	double** G = criarMatrizG(0, matriz_admitancias, size_barra);
	double** B = criarMatrizB(0, matriz_admitancias, size_barra);

	double teta_kj;
	double soma;
	//J é [dfp1/dt1 dfp1/dt2 dfp1/dt3 dfp1/dt4 dfp1/dV1 df1/dv2 dfp1/dv3];
	double** J = criarMatrizDinamica(2*nPQ + nPV,2*nPQ + nPV ); //matriz do jacobiano
	int k;

	/*fp em J*/
	for (int i=0; i< (nPQ + nPV); i++){
		soma = 0;
		for(int j=0; j<(2*nPQ + nPV); j++){
			if (j ==i){
				soma =0;
				for (k=0; k<size_barra; k++){
					if (k != i){
						teta_kj = teta[k] - teta[i];
						soma = soma + V[k]*(G[i][k]*sin(teta_kj)+B[i][k]*cos(teta_kj));
					}
				}
				J[i][j] = soma*V[i];
			}
			else if(j== (nPQ+nPV + i)){
				soma = 0;
				for (k=0; k<size_barra; k++){
					if  (k != i){
						teta_kj = teta[k]-teta[i];
						soma = soma + V[k]*(G[i][k]*cos(teta_kj)-B[i][k]*sin(teta_kj));
					}
				}
				J[i][j] = soma + 2*V[i]*G[i][i];
			}
			else if (j<= nPQ+nPV){
				k = j;
				teta_kj = teta[k] - teta[i];
				J[i][j] = -V[i]*V[k]*(G[i][k]*sin(teta_kj)+B[i][k]*cos(teta_kj));
			}
			else{
				k = j - nPQ -nPV;
				teta_kj = teta[k] - teta[i];
				J[i][j] = V[i]*(G[i][k]*cos(teta_kj)-B[i][k]*sin(teta_kj));
			}
		}
	}

	/*fq em J*/
	for (int i=0; i< nPQ; i++){
		soma = 0;
		for (int j=0; j<2*nPQ + nPV; j++){
			if (j == i){
				soma = 0;
				for (k=0; k<size_barra; k++){
					if (k != i){
						teta_kj = teta[k] - teta[i];
						soma = soma + V[k]*(G[i][k]*cos(teta_kj)-B[i][k]*sin(teta_kj));
					}
				}
				J[nPQ+nPV+i][j] = soma*V[i];
			}
			else if(j== (nPQ+nPV+i)){
				soma = 0;
				for (k=0; k<size_barra; k++){
					if (k!=i){
						teta_kj = teta[k] - teta[i];
						soma = soma + V[k]*(G[i][k]*sin(teta_kj)+B[i][k]*cos(teta_kj));
					}
				}
				J[nPQ+nPV+i][j] = -soma  - 2*V[i]*B[i][i];
			}
			else if (j<=(nPQ+nPV)){
				k = j;
				teta_kj = teta[k] - teta[i];
				J[nPQ+nPV+i][j] = -V[i]*V[k]*(G[i][k]*cos(teta_kj)-B[i][k]*sin(teta_kj));
			}
			else{
				k = j-nPQ-nPV;
				teta_kj = teta[k] - teta[i];
				J[nPQ+nPV+i][j] = -V[i]*(G[i][k]*sin(teta_kj)+B[i][k]*cos(teta_kj));

			}
		}
	}
	return J;
};


double* metodo_de_newton_stevenson(double* teta, double* V, int nPQ, int nPV, double** matriz_admitancias) {

	double erro = 1;
	double* x;
	double** J;
	double* F;
	double* c;
	int it =0;

	while(it < 2){
		J = calculo_J(teta, V, nPQ, nPV, matriz_admitancias);
		F = calculo_F(teta, V, nPQ, nPV, matriz_admitancias);
		c = resolucao_sistema_linear(J, F, (2*nPQ+nPV));
		erro = max_valor(c, (2*nPQ + nPV));
		x = soma_de_vetor(x, c, 2*nPQ + nPV);
		for(int i=0; i<nPQ; i++){
			V[i] = V[i] + c[nPQ + nPV +1 +i];
		}
		for(int i=0; i<(nPQ+nPV); i++){
			teta[i] = teta[i] + c[i];
		}
		it++;
	}
	return x;


	printf("Matriz V \n ");
	for (int i=0; i<2*nPQ+nPV; i++){
		printf("%le \n", V[i]);
	}

	printf("\n \n \n");

};
