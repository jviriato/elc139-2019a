#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

/*
 * Tempo (wallclock) em microssegundos
 */
long wtime()
{
   struct timeval t;
   gettimeofday(&t, NULL);
   return t.tv_sec*1000000 + t.tv_usec;
}

double dotprod_worker(double *a, double *b, int wsize, int repeat)
{
   double sum;
   for (int k = 0; k < repeat; k++) {
      sum = 0.0;
      for (int i = 0; i < wsize; i++)  {
         sum += (a[i] * b[i]);
      }
   }
   return sum;
}

void fill(double *a, float value_a, double *b, float value_b, int size)
{
   for (int i = 0; i < size; i++) {
      a[i] = value_a;
      b[i] = value_b;
   }
}

int main(int argc, char **argv)
{
   int num_proc = 0;
   int rank     = 0;
   int dest     = 0;
   int tag      = 0;
   double msg   = 0.0;
   double sum   = 0.0;

   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

   if ((argc != 3)) {
      printf("Uso: mpiexec -np <ntasks> %s <wsize> <repetitions>\n", argv[0]);
      MPI_Finalize();
      exit(EXIT_FAILURE);
   }

   int wsize, repeat;
   wsize = atoi(argv[1]);
   repeat = atoi(argv[2]);

   int chunks = wsize / num_proc;

   double *a = (double *) malloc(chunks*sizeof(double));
   double *b = (double *) malloc(chunks*sizeof(double));
   fill(a, 0.01, b, 1.0, chunks);

   long start_time, end_time;
   start_time = wtime();
   sum = dotprod_worker(a, b, chunks, repeat);
   end_time = wtime();

   if(rank == 0) {
      for(int i = 0; i < num_proc - 1; i++){
          MPI_Recv(&msg, 1, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      }
      sum = sum + msg;
      printf("%f\n", sum);
      printf("%ld usec\n", end_time - start_time);
   }else{
      MPI_Send(&sum, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
   }

   MPI_Finalize();
   free(a);
   free(b);
   return EXIT_SUCCESS;
}
