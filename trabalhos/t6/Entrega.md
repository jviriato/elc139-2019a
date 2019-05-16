# Entrega
[Programação Paralela](https://github.com/jviriato/elc139-2019a) > [Trabalhos](trabalhos) > [t6](/trabalhos/t6)

**Nome**: José Victor Viriato

**Disciplina**: Programação Paralela

**Specs**:

Sistema Operacional: Ubuntu 18.04

Memória RAM: 8GB

Processador: Intel(R) Core(TM) i5-5200U

Frequência: 2.20GHz

Núcleos: 2

## Parte 1

* Adição de **MPI_Bcast**: Transmite uma mensagem do processo com rank "root" para todos os outros processos [1]

* Adição de **MPI_Scatter**: Transmite dados de um processo para todos em um comunicador [2]

Enquanto *MPI_Bcast* envia o mesmo dado para todos, o *MPI_Scatter* envia um pedaço da array para cada processo;

*MPI_Gather* é o inverso de *MPI_Scatter*.

![3](exemplo.png)

[matrix_mult_sr_fixed.c](matrix_mult_sr_fixed.c)


## Parte 2


## Referências
[1] [MPI_Bcast](https://www.mpich.org/static/docs/v3.2/www3/MPI_Bcast.html)
[2] [MPI_Scatter](https://www.mpich.org/static/docs/v3.1/www3/MPI_Scatter.html)
[3] [MPI Scatter, Gather, and Allgather](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/zh_cn/)
