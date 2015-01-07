
/* Includes, system */
#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>
#define N 1024
#define BLOCK_SIZE 512

/* DEVICE CODE */

__global__ void IntProd(int* intprodParcial,int* d1,int* d2){

    __shared__ double accumResult[BLOCK_SIZE];

    int pos = blockIdx.x * blockDim.x + threadIdx.x;
    int iAccum = threadIdx.x;	
    int vec =  blockIdx.x;

//    accumResult[iAccum] = d1[pos] * d2[pos];
    accumResult[iAccum] = d1[pos];

    for(int stride = BLOCK_SIZE / 2; stride > 0; stride >>= 1){
        __syncthreads();
        accumResult[iAccum] += accumResult[stride + iAccum];
    }

    if(threadIdx.x == 0) {
        intprodParcial[vec] = accumResult[0];
    }
}



__global__ void suma_2_enteros(int *d1, int *d2, int *sum){

        int idBloque = blockIdx.y * gridDim.x + blockIdx.x;
        int idThread = idBloque * blockDim.z * blockDim.y * blockDim.x + threadIdx.z * blockDim.y * blockDim.x + threadIdx.y * blockDim.x + threadIdx.x;
	sum[idThread] = d1[idThread] + d2[idThread];
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


    for (i=0;i<N;i++){h_d1[i]=i;h_d2[i]=i;h_sum[i]=0;}	
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

     IntProd<<<2,BLOCK_SIZE>>>(d_sum,d_d1,d_d2);

     cudaMemcpy(h_sum,d_sum,N*sizeof(h_sum[0]),cudaMemcpyDeviceToHost);

     printf("Resultado: %d \n",h_sum[0]+h_sum[1]);
     cudaFree(d_d1);cudaFree(d_d2);cudaFree(d_sum);
}
