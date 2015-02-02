#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char *argv[])
{


int *v, **m, *resultado, *v1, i, j, nproces, myrank, N;
int tambloque;

MPI_Status status;

MPI_Init(&argc,&argv);



 MPI_Comm_size(MPI_COMM_WORLD,&nproces);
 MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

 N=atoi(argv[1]);

 tambloque=N/nproces;

//reserva e inicializacion del proceso padre
if (myrank == 0)
{

 	m = (int**)malloc(N*sizeof(int*));
 	v = (int*)malloc(N*sizeof(int));
 	resultado = (int*)malloc(N*sizeof(int));

 	for(i = 0; i < N; i++)
 	{
 		m[i] = (int*)malloc(N*sizeof(int));
 		v[i] = 2;
 	}

 	for(i = 0; i < N; i++)
 	{
 		for(j = 0; j < N; j++)
 		{
 			m[i][j] = 2;
 		}
 	}

 	MPI_Bcast(v, N, MPI_INT, 0, MPI_COMM_WORLD);

 	for(i = 1; i < nproces; i++)
 	 {
 	 	MPI_Send(m[i], N,MPI_INT,i,1,MPI_COMM_WORLD);
 	 }
 }
 else
 {
 	v1 = (int*)malloc(N*sizeof(int));
 	v = (int*)malloc(N*sizeof(int));

 	 
 	
 	MPI_Bcast(v, N, MPI_INT, 0, MPI_COMM_WORLD);

 	
 	
 	MPI_Recv(v1, N,MPI_INT, 0, 1, MPI_COMM_WORLD,&status);
 	
 	

 }

 printf("\nSoy el proceso %d de %d procesos y mi vector es: ",myrank, nproces);

 for(i=0; i<N; i++)
 {
 	printf("%d ",v[i]);
 	printf("%d\n",v1[i]);
 }
  	
  printf("\n");

MPI_Finalize();
}