#rm *.o
#rm *.out
#cp nlcg_cuda.c nlcg_cuda.cu
nvcc -use_fast_math -arch sm_13 -lcuda  -o cudaej cudaej0.cu
