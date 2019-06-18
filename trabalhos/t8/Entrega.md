# Entrega
[Programação Paralela](https://github.com/jviriato/elc139-2019a) > [Trabalhos](trabalhos) > [t8](/trabalhos/t8)

**Nome**: José Victor Viriato

**Disciplina**: Programação Paralela

**Specs**

GPU: Tesla T4

## Parte 1

O código pode ser conferido: [wavecuda1.cu](wavecuda1.cu)

Executando 10 vezes cada programa, temos a seguinte tabela:

|     Código    | Tamanho | Quantidade |   Tempo  |
|:-------------:|:-------:|:----------:|:--------:|
|    wave.cpp   |   512   |     100    |  1.2996s |
| wavecuda1.cpp |   512   |     100    |  0.2615s |
|    wave.cpp   |   1024  |     100    |  5.3739s |
| wavecuda1.cpp |   1024  |     100    |  0.6194s |
|    wave.cpp   |   1024  |     200    | 10.5785s |
| wavecuda1.cpp |   1024  |     200    |  0.6609s |
|    wave.cpp   |   2048  |     100    | 20.8395s |
| wavecuda1.cpp |   2048  |     100    |  2.0350s |

A paralelização com GPU neste caso é excelente, diminuindo em grande quantidade o tempo de processamento.
Ao analisarmos o nvprof gerado, percebemos que grande quantidade do tempo é gasto na chamada da API *cudaDeviceSynchronize*, este é o método que sincroniza entre os kernels, forçando o programa a aguardar até que todas os comandos em todas as streams acabem, só então podendo continuar.

## Referências
* [Cuda Toolkit Documentation](https://docs.nvidia.com/cuda/)
