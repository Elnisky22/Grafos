#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

#define MAX_TAMANHO 20

double A[MAX_TAMANHO][MAX_TAMANHO*3];
double b[MAX_TAMANHO];
char igualdades[MAX_TAMANHO];
double C[MAX_TAMANHO*3];
double CF1[MAX_TAMANHO*3];

int minMax = 0;
int numVariaveis = 0;
int numRestricoes = 0;
int numVarFolga = 0;
int numVarArtificial = 0;

// Função para gerar a transposta da Matriz parâmetro
double ** transpor(int ordem, double *matriz[ordem]) {
	double **M = (double **) calloc(ordem, sizeof(double *));
	for (int i = 0; i < ordem; ++i) {
		M[i] = (double *) calloc (ordem, sizeof(double));
	}

	for (int i = 0; i < ordem; i++) {
		for (int j = 0; j < ordem; j++) {
			M[i][j] = matriz[j][i];
		}
	}
	return M;
}

//cria uma submatriz da matriz original com as colunas dos parametros
double ** criarSubMatriz(int largCol, int numLin, int numCol, double matriz[][largCol], int vetColunas[]){

	double **M = (double **) calloc(numLin, sizeof (double *));
	for (int i = 0; i < numLin; ++i){
		M[i] = (double *) calloc (numCol, sizeof (double));
	}

	for (int i = 0; i < numCol; i++){
		for (int j = 0; j < numLin; j++){
			M[j][i] = matriz[j][vetColunas[i]];
		}
	}

	return M;
}

// Função para o cálculo do Gauss
double * gauss(int ordem, double *matriz[ordem], double res[ordem]){
	double *result = (double*) calloc(ordem, sizeof(double));
	memcpy(result, res, ordem*sizeof(double));
	
	double **M = (double **) calloc(ordem, sizeof(double *));
	for (int i = 0; i < ordem; ++i) {
		M[i] = (double *) calloc (ordem, sizeof(double));
		memcpy(M[i], matriz[i], ordem * sizeof(double));
	}

	int i,j,k;
	for (j = 0; j < ordem; j++) {
		for (i = j+1; i < ordem; i++) {
			double c = M[i][j]/M[j][j];
			for (k = 0; k < ordem; k++) {
				M[i][k] -= c*M[j][k];
			}
			result[i] -= c*result[j];
		}
	}

	for (i = ordem-1; i >= 0; i--) {
		double sum = 0.0;
		for (j = i+1; j < ordem; j++) {
			sum += M[i][j]*result[j];
		}
		result[i] = (result[i]-sum)/ M[i][i];
	}
	return result;
}

// Função para colocar o problema na forma padrão
int preparaformaPadrao() {
	numVarFolga = numVariaveis + numRestricoes;

	if (minMax > 0) {
		for (int i = 0; i < numVarFolga; i++) {
			C[i] *= -1.0;
		}
	}

	for (int i = 0; i < numRestricoes; i++) {
		if(b[i] < 0){
			b[i] *= -1.0;
			if(igualdades[i] != '='){
				if (igualdades[i] == '<')
					igualdades[i] = '>';
				else
					igualdades[i] = '<';
			}
			for (int j = 0; j < numVarFolga; j++){
				A[i][j] *= -1.0;
			}
			
		}
	}

	int retFlag = 0 ;

	for (int i = 0; i < numRestricoes; i++) {
		if (igualdades[i] == '=') {
			retFlag=1;
			continue;
		}
		if (igualdades[i] == '>') {
			A[i][i+numVariaveis]=-1;
			retFlag=1;
		}
		else if (igualdades[i] == '<')
			A[i][i+numVariaveis]=1;
	}
	return retFlag;
}

// Função para preparar o problema para a Fase 1
void preparaFase1() {
	numVarArtificial = numVarFolga + numRestricoes;
	for (int i = 0; i < numVarArtificial; i++)
		CF1[i] = 0;
	
	for (int i = 0; i < numRestricoes; i++){
		A[i][i+numVarFolga] = 1.0;
		CF1[i+numVarFolga] = 1.0;
	}
}

void simplex(int maxIteracoes) {
	//flag da fase 1
	int flagF1 = preparaformaPadrao();
	
	int iteracao = 0;
	int basicas[numRestricoes];
	int naoBasicas[numVariaveis+(numRestricoes*flagF1)];

	double *xb;
	if(flagF1){
		preparaFase1();
		for (int i = 0; i < numRestricoes; i++)
			basicas[i] = i + numVarFolga;
		for (int i = 0; i < numVarFolga; i++)
			naoBasicas[i] = i;
	}else{
		for (int i = 0; i < numRestricoes; i++)
			basicas[i] = i + numVariaveis;
		for (int i = 0; i < numVariaveis; i++)
			naoBasicas[i] = i;
	}

	while (iteracao < maxIteracoes) {
		iteracao++;
		
		if (flagF1) printf("\n\n\nFase 1 ");
		else printf("\n\n\nFase 2 ");
		
		printf("Iteracao: %d\n", iteracao);
		printf("\nPasso 1: Calculo da Solucao Basica\n");
		double **B = criarSubMatriz(MAX_TAMANHO*3, numRestricoes,numRestricoes, A,basicas);
		xb = gauss(numRestricoes, B, b);
		printf("XB:\n");
		for (int i = 0; i < numRestricoes; i++) {
			printf("%.4lf | ",xb[i]);
		}
		//Passo 2: {Cálculo dos custos relativos}
			printf("\n\nPasso 2.1: Vetor multiplicador Simplex\n");
			double **Btrans = transpor(numRestricoes,B);
			double CB[numRestricoes];
			for (int i = 0; i < numRestricoes; i++) {
				if (flagF1)
					CB[i] = CF1[basicas[i]];
				else
					CB[i] = C[basicas[i]];
			}

			double *lambda = gauss(numRestricoes, Btrans, CB);
			
			printf("Lambda:\n");
			for (int i = 0; i < numRestricoes; i++) {
				printf("%lf | ", lambda[i]);
			}

			printf("\n\nPasso 2.2: Custos Relativos\n");
			//fase 1 muda
			int tamanhoCN = numVariaveis;
			if (flagF1)
				tamanhoCN = numVarFolga;
			
			double CN[tamanhoCN];
			
			for (int i = 0; i < tamanhoCN; i++) {
				double multiplicacao = 0.0;
				for (int j = 0; j < numRestricoes; j++) {
					multiplicacao += lambda[j]*A[j][naoBasicas[i]];
				}
				
				CN[i] = C[naoBasicas[i]]-multiplicacao;
			}

			for (int i = 0; i < tamanhoCN; i++) {
				printf("x%d = %lf | ",naoBasicas[i], CN[i]);
			}

			printf("\n\nPasso 2.3: Determinacao da Variavel a entrar na base\n");
			int k = 0;
			for (int i = 0; i < tamanhoCN; i++) {
				if (CN[i] < CN[k]) k = i;
			}
			
			printf("Variavel (%d) entrara na base", naoBasicas[k]);

		printf("\n\nPasso 3: Teste de otimalidade\n");
		//fase 1 muda
		if (CN[k] >= 0.0) {
			if(flagF1){
				for (int i = 0; i < numRestricoes; i++){
					if(basicas[i]>=numVarFolga){
						printf("Problema infactivel");
						flagF1 = 0;
						return;
					}
				}
				if (flagF1){
					printf("Fim da fase 1: iteracoes: %d", iteracao);
					iteracao = 0;
					for (int i = 0; i < numVariaveis; i++){
						while(naoBasicas[i]>=numVarFolga){
							for (int j = 0; j < numVarFolga - (i+1); j++){
								naoBasicas[j]=naoBasicas[j+1];
							}
						}
					}
					continue;
				}
			}else{
				printf("A solucao na iteracao atual eh otima.\n");
				break;
			}
		}else{
			printf("a solucao nao eh otima");
		}

		printf("\n\nPasso 4: Calculo da direcao simplex\n");
		double Ank[numRestricoes];
		for (int i = 0; i < numRestricoes; i++) {
				Ank[i] = A[i][k];
		}
		double *y = gauss(numRestricoes, B, Ank);

		printf("Valores de Y:\n");
		for (int i = 0; i < numRestricoes; i++) {
				printf("%.4lf | ", y[i]);
		}

		printf("\n\nPasso 5: determinacao do passo e variavel a sair da base\n");
		// fase 1 muda
		double e = INFINITY;
		int l = -1;
		for (int i = 0; i < numRestricoes; i++) {
			if (y[i] > 0.0) {
				if (e > xb[i] / y[i]){
					e = xb[i] / y[i];
					l = i;
				}
			}
		}
		if (l == -1) {
			printf("\nProblema nao tem solucao otima finita\n");
			if(flagF1) 
				printf("portanto o problema original eh Infactivel\n");
			return;
		}else{
			printf("variavel (%d) sai da base (divizao minima= %lf)",basicas[l],e);
		}

		printf("\n\nPasso 6: Atualizacao da particao basica\n");
		//fase 1 muda
		int temp = basicas[l];
		basicas[l] = naoBasicas[k];
		naoBasicas[k] = temp;

		printf("basicas = ");

		for (int i = 0; i < numRestricoes; i++){
			printf("%d | ",basicas[i]);
		}
		printf("\nnao basicas = ");

		for (int i = 0; i < numVariaveis+(numRestricoes*flagF1); i++){
			printf("%d | ",naoBasicas[i]);
		}

		if (flagF1){
			int flagFimF1 = 1;
			for (int i = 0; i < numRestricoes; i++){
				if(basicas[i]>=numVarFolga){
					flagFimF1 = 0;
				}
			}

			if(flagFimF1){
				printf("\n\nFim da fase 1 (sem variaves artificiais na base) iteracoes:%d\n", iteracao);
				iteracao = 0;
				flagF1 = 0;
				for (int i = 0; i < numVariaveis; i++){
					while(naoBasicas[i]>=numVarFolga){
						for (int j = i; j < numVarFolga - (i+1); j++){
							naoBasicas[j]=naoBasicas[j+1];
						}
					}
				}
			}
		}
	}


	printf("Fim do Simplex, iteracoes: %d\nResultado:\n", iteracao);
	double resp[numVariaveis];
	for (int i = 0; i < numVariaveis; i++) {
		int j;
		for (j = 0; j < numRestricoes; j++){
			if(basicas[j] == i){
				printf("x%d = %.4lf\n",i,xb[j]);
				resp[i] = xb[j];
				break;
			}
		}
		if(j>=numRestricoes){
			printf("x%d = 0.0000\n",i);
			resp[i] = 0.0;
		}
	}
	double fx = 0.0;
	for (int i = 0; i < numVariaveis; i++){
		fx += resp[i]*C[i];
	}
	if(minMax>0) fx *= -1;
	printf("\nf(x) = %.4lf",fx);
}

int main() {
	printf("Min ou max (-1: min, 1: max): ");
	scanf("%d", &minMax);
	printf("Quantidade de variaveis: ");
	scanf("%d", &numVariaveis);
	printf("\nQuantidade de restricoes: ");
	scanf("%d", &numRestricoes);
	printf("\n");

	if ((numRestricoes > MAX_TAMANHO) || (numVariaveis + (numRestricoes * 2) > MAX_TAMANHO * 3)) {
		printf("Problema com tamanho muito grande\naltere a constante \"MAX_TAMANHO\" ou entre com outro problema");
		return -1;
	}

	for (int i = 0; i < numVariaveis; i++) {
		printf("\nInforme o custo de x%d: ", i);
		scanf("%lf", &C[i]);
	}

	for (int j = 0; j < numRestricoes; j++) {
		for (int i = 0; i < numVariaveis; i++) {
			printf("\nInforme a constante que multiplica x%d na restricao %d: ", i, j);
			scanf("%lf", &A[j][i]);
		}

		printf("\nInforme a (des)igualdade da restricao %d (< ou = ou >): ", j);
		fflush(stdin);
		scanf("%c", &igualdades[j]);

		printf("\nInforme o b da restricao %d: ", j);
		scanf("%lf", &b[j]);
	}

	printf("\nA=\n");
	for (int j = 0; j < numRestricoes; j++) {
		for (int i = 0; i < numVariaveis; i++) {
			printf("%lf |", A[j][i]);
		}
		printf("\n");
	}

	printf("\nb=\n");
	for (int j = 0; j < numRestricoes; j++) {
		printf("%lf |", b[j]);
		printf("\n");
	}

	printf("\nC=\n");
	for (int i = 0; i < numVariaveis; i++) {
		printf("%lf |", C[i]);
	}	

	printf("\ninforme o numero maximo de iteracoes do simplex\n");
	int maxI;
	scanf("%d",&maxI);

	simplex(maxI);

	return 0;
}
