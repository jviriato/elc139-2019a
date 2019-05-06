#include "mpi.h"
#include <iostream>
#include <ctime>

int main(int argc, char** argv)
{
    int num_rank = 0;
    int num_proc = 0;
    int msg_int  = 8;
    int dest     = 0;
    int tag      = 0;
    int src      = 0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &num_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    if (num_rank == 0) {
        std::cout << "Início..." << std::endl;
        std::cout << "Processo " << num_rank;
        std::cout << " enviando msg inicial: " << msg_int << std::endl;
        dest = num_rank + 1;
        msg_int++;
        MPI_Send(&msg_int, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    } else if (num_rank != num_proc - 1) {
        src = num_rank - 1;
        MPI_Recv(&msg_int, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
        std::cout << "Processo " << num_rank << " recebeu: " << msg_int << std::endl;
        msg_int++;
        dest = num_rank + 1;
        MPI_Send(&msg_int, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    } else {
        src = num_rank - 1;
        MPI_Recv(&msg_int, 1, MPI_INT, src, tag, MPI_COMM_WORLD, &status);
        std::cout << "Processo " << num_rank << " (final) recebeu: " << msg_int << std::endl;
    }
    MPI_Finalize();
    return 0;
}

