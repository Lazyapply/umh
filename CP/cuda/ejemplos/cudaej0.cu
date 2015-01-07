
/* Includes, system */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

/* Includes, cuda */
#include <cuda.h>
#include <cuda_runtime.h>

#define N 1000000
#define GRID 100000
#define BLOCK 100
#define M 1000

/* Main */
int main(int argc, char** argv)
{

    double *h_x,*h_y;
    double *d_x,*d_y;
    int n=N,num_err=0;
    int DeviceCount = 0;

    /* Initialize CUDA */
    printf("CUDA 0  ejemplo..\n");

    if (cuInit(0) != CUDA_SUCCESS){
        printf("ERROR de inicializacion\n");
        exit(0);
	}
    cuDeviceGetCount(&DeviceCount);
    if (DeviceCount == 0){
        printf("ERROR ningun dispositivo soporta CUDA\n");
        exit(0);
	}
    /* Allocate host memory for the matrices */
    h_x = (double*)malloc(n * sizeof(h_x[0]));
    h_y = (double*)malloc(n * sizeof(h_y[0]));

    memset(h_x,2,n * sizeof(h_x[0]));
    memset(h_y,4,n * sizeof(h_x[0]));

    if (cudaMalloc((void**)&d_x,n*sizeof(d_x[0])) != 0) num_err++;
    if (cudaMalloc((void**)&d_y,n*sizeof(d_y[0])) != 0) num_err++;

    if (num_err != 0) {
        printf ("ERROR reserva memoria device: %d\n",num_err);
        return EXIT_FAILURE;
    }

    if (cudaMemcpy(d_x,h_x,n*sizeof(d_x[0]),cudaMemcpyHostToDevice) != 0) printf("ERROR1") ;
    if (cudaMemcpy(d_y,h_y,n*sizeof(d_y[0]),cudaMemcpyHostToDevice) != 0) printf("ERROR2") ;

    //LLAMADA A KERNEL QUE MODIFICA MEMORIA DEVICE	

    if (cudaMemcpy(h_x,d_x,n*sizeof(h_x[0]),cudaMemcpyDeviceToHost) != 0) printf("ERROR3") ;
    if (cudaMemcpy(h_y,d_y,n*sizeof(h_y[0]),cudaMemcpyDeviceToHost) != 0) printf("ERROR4") ;

    free(h_x);
    free(h_y);

    cudaFree(d_x);
    cudaFree(d_y);

    return EXIT_SUCCESS;
}
