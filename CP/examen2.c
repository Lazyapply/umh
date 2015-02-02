#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


#define tMatriz 120

int main(int argc, char *argv[]){

	int 	i=0, j=0, iam, np=1, tBloque, *vResultado, aux;
	int	**mA, **mB, **mC;





	//el número de procesos viene del primer argumento
	//y el tamaño de N del segundo.
	np 		= atoi(argv[1]);
	tBloque = tMatriz/np;

	//reservamos memoria
	vResultado	= (int*) malloc(tMatriz * sizeof(int));
	mA 		= (int**) malloc(tMatriz * sizeof(int*));
	mB 		= (int**) malloc(tMatriz * sizeof(int*));
	mC 		= (int**) malloc(tMatriz * sizeof(int*));

	for(i=0;i<tMatriz;i++){

		mA[i] = (int*) malloc(tMatriz * sizeof(int));
		mB[i] = (int*) malloc(tMatriz * sizeof(int));
		mC[i] = (int*) malloc(tMatriz * sizeof(int));

		for(j=0;j<tMatriz;j++){
			mA[i][j] = rand()%9;
			mA[i][j] = rand()%9;
			mC[i][j] = 0;
		}
	}

	#pragma omp parallel num_threads(np) private(iam, i, j, aux) default(shared)
	{
		iam = omp_get_thread_num();

		for(i=0;i<tMatrizF;i++){

			aux = 0;
			aux += mA[i][iam*tBloque+j] * mB[i][iam*tBloque+j] + mA[i][iam*tBloque+j];
		}

		#pragma omp critical
		{
			vResultado[i] += aux;
		}
	}


}