#include <omp.h>
#include <stdio.h>
int main()
{
   int iam =0, np = 1;
#pragma omp parallel num_threads(4)
{
   np = omp_get_num_threads();
   iam = omp_get_thread_num();
   printf("Hola Mundo: soy el proceso %d de %d procesos.\n",iam,np);
}
printf("Adios Mundo: soy el proceso %d de %d procesos.\n",iam,np);

}
