
/* Includes, system */
#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>
#define N 512

/* DEVICE CODE */
__global__ void suma_2_enteros(int *d1, int *d2, int *sum){
	sum[threadIdx.x] = d1[threadIdx.x] + d2[threadIdx.x];
}

/* HOST CODE*/
int main(int argc, char** argv)
{
    int DeviceCount = 0,i;
    int *h_d1,*h_d2,*h_sum;
    int *d_d1,*d_d2,*d_sum;

    h_d1 = (int*)malloc(N * sizeof(h_d1[0]));
    h_d2 = (int*)malloc(N * sizeof(h_d2[0]));
    h_sum = (int*)malloc(N * sizeof(h_sum[0]));

    for (i=0;i<N;i++){h_d1[i]=i;h_d2[i]=10*i;h_sum[i]=0;}	
    /* Initialize CUDA */
    if (cuInit(0) != 0){
        printf("ERROR de inicializacion\n");
        exit(0);
        }
    cuDeviceGetCount(&DeviceCount);
    if (DeviceCount == 0){
        printf("ERROR ningun dispositivo soporta CUDA\n");
        exit(0);
        }
    cudaMalloc((void**)&d_d1,N*sizeof(d_d1));cudaMemset(d_d1,0,N*sizeof(d_d1));
    cudaMalloc((void**)&d_d2,N*sizeof(d_d2));cudaMemset(d_d2,0,N*sizeof(d_d2));
    cudaMalloc((void**)&d_sum,N*sizeof(d_sum));cudaMemset(d_sum,0,N*sizeof(d_sum));

    cudaMemcpy(d_d1,h_d1,N*sizeof(h_d1[0]),cudaMemcpyHostToDevice);
    cudaMemcpy(d_d2,h_d2,N*sizeof(h_d2[0]),cudaMemcpyHostToDevice);

     suma_2_enteros<<<1,512>>>(d_d1,d_d2,d_sum);

     cudaMemcpy(h_sum,d_sum,N*sizeof(h_sum[0]),cudaMemcpyDeviceToHost);

     for (i=0;i<10;i++) printf("Resultado: %d \n",h_sum[i]);
     cudaFree(d_d1);cudaFree(d_d2);cudaFree(d_sum);
}
