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

	//inicializacion
	printf(""YELLOW"CUDA0"RESET" ejemplo\n");

	//comprobamos que la inicializacion sea correcta
	if(cuInit(0) != CUDA_SUCCESS){
		printf(""RED"ERROR de inicializacion"RESET"\n");
		exit(0);
	}
	else
		printf(""GREEN"Inicializacion correcta"RESET"\n");

	//vemos el numero de dispositivos compatibles
	cuDeviceGetCount(&DeviceCount);
	if(DeviceCount == 0){
		printf(""RED"ERROR, ningun dispositivo compatible con CUDA"RESET"\n");
		exit(0);
	}
	else
		printf(""GREEN"%d dispositivos compatibles con CUDA"RESET"\n", DeviceCount);
	
	//reservamos memoria para las matrices en HOST
	h_x = (double*)malloc(n * sizeof(h_x[0]));
	h_y = (double*)malloc(n * sizeof(h_y[0]));

	//inicializamos valores
	memset(h_x, 2, n * sizeof(h_x[0]));
	memset(h_y, 2, n * sizeof(h_y[0]));


	//reservamos para el DEVICE
	//cudaMalloc(devPtr, size)
	//devPtr -> puntero para el DEVICE
	//size -> tamaño en bytes
	if(cudaMalloc((void**)&d_x, n * sizeof(d_x[0])) != 0) numErr++;
	if(cudaMalloc((void**)&d_y, n * sizeof(d_y[0])) != 0) numErr++;

	//comprobamos que no hay errores
	if(numErr != 0){
		printf(""RED"ERROR, reserva de memoria en DEVICE"RESET"\n");
		return EXIT_FAILURE;
	}

	//copiamos datos de memoria
	//cudaMemcpy(dst, src, size_t, kind)
	//dst -> direccion de memoria de destino
	//src -> direccion de memoria origen
	//size_t -> tamaño en bytes para copiar
	//kind -> tipo de transferencia
	if(cudaMemcpy(d_x, h_x, n * sizeof(d_x[0]), cudaMemcpyHostToDevice) != 0)
		printf(""RED"ERROR, transferencia HOST-->DEVICE (d_x)"RESET"\n");

	if(cudaMemcpy(d_y, h_x, n * sizeof(d_y[0]), cudaMemcpyHostToDevice) != 0)
		printf(""RED"ERROR, transferencia HOST-->DEVICE (d_y)"RESET"\n");



	//llamada al kernel (recogemos los datos del kernel)
	if(cudaMemcpy(h_x, d_x, n * sizeof(d_x[0]), cudaMemcpyDeviceToHost) != 0)
		printf(""RED"ERROR, transferencia DEVICE-->HOST (d_x)"RESET"\n");

	if(cudaMemcpy(h_x, d_y, n * sizeof(d_y[0]), cudaMemcpyDeviceToHost) != 0)
		printf(""RED"ERROR, transferencia DEVICE-->HOST (d_y)"RESET"\n");

	//liberamos memoria del HOST
	free(h_x);
	free(h_y);

	//liberamos memoria del DEVICE
	cudaFree(d_x);
	cudaFree(d_y);

	return EXIT_SUCCESS;
}