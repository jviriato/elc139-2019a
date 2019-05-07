# Entrega
[Programação Paralela](https://github.com/jviriato/elc139-2019a) > [Trabalhos](trabalhos) > [t5](/trabalhos/t5)

**Nome**: José Victor Viriato

**Disciplina**: Programação Paralela

**Specs**:

Sistema Operacional: Ubuntu 18.04

Memória RAM: 8GB

Processador: Intel(R) Core(TM) i5-5200U

Frequência: 2.20GHz

Núcleos: 2

## Parte 1

Cada tabela é o resultado da média de 20 execuções na shell.

| Tamanho do vetor | Repetições |  1 processo  |  2 processos |  4 processos |  8 processos | Speedup 2 | Speedup 4 | Speedup 8 |
|:----------------:|:----------:|:------------:|:------------:|:------------:|:------------:|:---------:|:---------:|:---------:|
|      2000000     |    1000    | 7127151 usec | 3885481 usec | 3005158 usec | 2994674 usec |    1.83   |    2.37   |    2.38   |
|      1000000     |    1000    | 3564268 usec | 1917248 usec | 1491557 usec | 1480358 usec |    1.85   |    2.38   |    2.40   |
|       10000      |    1000    |  38143 usec  |  18395 usec  |  13641 usec  |   9713 usec  |    2.07   |    2.79   |    3.9    |
|      2000000     |     500    | 3567306 usec | 1937589 usec | 1520242 usec | 1500875 usec |    1.84   |    2.34   |    2.37   |
|      1000000     |     500    | 1779271 usec |  969698 usec |  777537 usec |  726926 usec |    1.83   |    2.28   |    2.44   |
|       10000      |     500    |  18082 usec  |  11204 usec  |   6807 usec  |   3560 usec  |    1.61   |    2.65   |     5     |

Um fato curioso foi o speedup absurdo de 8 processos para um valor pequeno (3.9 e 5). No geral, tem-se um ganho considerável com 4 processos, o ganho com 8 só pareceu realmente efetivo nos vetores menores.

## Parte 2

[mpi_errado1.c](mpi_errado1.c)
[mpi_errado2.c](mpi_errado2.c)


## Parte 3

[mpi_pipeline.cpp](mpi_pipeline.cpp)
