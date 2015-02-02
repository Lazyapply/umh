#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define tamVector 12


int main(int argc, char *argv[]){

	int 		i, j, myrank, nproces, resultadoParcial, resultadoTotal, tbloque, aux;
	double		*vector1, *vector2;
	MPI_Status	status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	tbloque = tamVector/nproces;

	if(myrank == 0){

		//reservamos memoria
		vector1 = (double*)malloc(tamVector * sizeof(double));
		vector2 = (double*)malloc(tamVector * sizeof(double));

		//inicializamos
		for(i=0;i<tamVector;i++){

			vector1[i] = rand()%9;
			vector2[i] = rand()%9;
		}

		//envios
			//no consigo sacar como enviar una vez a cada uno, si el indice, pero no el destinatario...
			for(i=0;i<tbloque;i++){
				//MPI_Send(matriz[i], tam, MPI_INT, i, 4, MPI_COMM_WORLD);
				MPI_Send(vector1[myrank+nproces*i], 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD);
				//printf(" %d[%d] ", (myrank+nproces*i), i/nproces);
			}

		}
	}
	else{
		//debemos recoger los datos
	}
	
	
	//calculamos
	//
	//
	//hacemos un reduce
	//
	//listo


	MPI_Finalize();
}