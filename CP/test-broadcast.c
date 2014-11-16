#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	int nproces, myrank, i, err;
	double data1 = 0, data2 = 0;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	
		
		if(myrank > 0){
			err = MPI_Bcast(&data1, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		}
		else{
			data1 = 33;
			err = MPI_Bcast(&data1, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		}

		printf("Proceso %d ->> data1: %f, data2 %f.\n", myrank, data1, data2);


	MPI_Finalize();
}