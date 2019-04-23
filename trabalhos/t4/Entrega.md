# Entrega
[Programação Paralela](https://github.com/jviriato/elc139-2019a) > [Trabalhos](trabalhos) > [t4](/trabalhos/t4)

**Nome**: José Victor Viriato

**Disciplina**: Programação Paralela

[fractalpar1.cpp](fractal/openmp_fractal/fractalpar1.cpp)

[fractalpar2.cpp](fractal/openmp_fractal/fractalpar2.cpp)

[Slides](t4paralela.pdf)

|     Tipo    | Tamanho | Frames |   Tempo  | Threads | Speedup |
|:-----------:|:-------:|:------:|:--------:|:-------:|:-------:|
|  Sequencial |   1024  |   32   |  43.90s  |    1    |    1        |
|  Sequencial |   1024  |   64   |  84.14s  |    1    |    1        |
|  Sequencial |   2048  |   32   |  175.45s |    1    |    1        |
|  Paralelo 1 |   1024  |   32   |    25s   |    2    |    1.75     |
|  Paralelo 1 |   1024  |   32   |  15.65s  |    4    |    2.80     |
|  Paralelo 1 |   1024  |   32   |  15.98s  |    8    |    2.74     |
|  Paralelo 1 |   1024  |   64   |  48.37s  |    2    |    1.74     |
|  Paralelo 1 |   1024  |   64   |  32.16s  |    4    |    2.61     |
|  Paralelo 1 |   1024  |   64   |  31.82s  |    8    |    2.64     |
|  Paralelo 1 |   2048  |   32   |  101.94s |    2    |    1.72     |
|  Paralelo 1 |   2048  |   32   |   66.2s  |    4    |    2.65     |
|  Paralelo 1 |   2048  |   32   |  67.61s  |    8    |    2.59     |
|  Paralelo 2 |   1024  |   32   |  23.94s  |    2    |    1.83     |
|  Paralelo 2 |   1024  |   32   |  14.80s  |    4    |    2.96     |
|  Paralelo 2 |   1024  |   32   |  15.09s  |    8    |    2.90     |
|  Paralelo 2 |   1024  |   64   |  47.57s  |    2    |    1.76     |
|  Paralelo 2 |   1024  |   64   |  29.65s  |    4    |    2.83     |
|  Paralelo 2 |   1024  |   64   |  30.44s  |    8    |    2.76     |
|  Paralelo 2 |   2048  |   32   |  100.37s |    2    |    1.74     |
|  Paralelo 2 |   2048  |   32   |  63.84s  |    4    |    2.74     |
|  Paralelo 2 |   2058  |   32   |  65.29s  |    8    |    2.68     |

  ## Referências

- [RookieHPC](https://rookiehpc.com/openmp/docs/)  
  Documentação do OpenMP.
