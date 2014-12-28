#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "colors.h"

#include <cuda.h>
#include <cuda_runtime.h>

#define N 		1000000
#define GRID	100000
#define BLOCK	100
#define M 		1000

int main(int argc, char *argv[]){

	double 	*h_x, *h_y; //variables del HOST
	double 	*d_x, *d_y; //variables del DEVICE
	int 	n 			= N;
	int 	numErr 		= 0;
	int 	DeviceCount = 0;

	//reservamos memoria para el HOST
	h_x = (double*) malloc(n * sizeof(h_x[0]));
	h_y = (double*) malloc(n * sizeof(h_y[0]));

	//inicializamos las variables
	memset(h_x, 2, n * sizeof(h_x[0]));
	memset(h_y, 2, n * sizeof(h_x[0]));

	if(cudaMalloc((void**)&d_x, n * sizeof(d_x[0])) != 0)
		numErr++;
	if(cudaMalloc((void**)&d_y, n * sizeof(d_y[0])) != 0)
		numErr++;

	if(numErr !=0){
		printf("ERROR reserva de memoria device %d\n", numErr);
		return EXIT_FAILURE;
	}
	else
		printf(""GREEN"Todo ok"RESET"\n");

}