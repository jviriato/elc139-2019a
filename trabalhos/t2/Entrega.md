# Entrega
[Programação Paralela](https://github.com/jviriato/elc139-2019a) > [Trabalhos](trabalhos) > [t2](/trabalhos/t2)

**Nome**: José Victor Viriato

**Disciplina**: Programação Paralela

**Especificações do Sistema**: [specs.txt](/trabalhos/t2/specs.txt)

**Resultados**: [results.csv](/trabalhos/t2/results.csv)



### Pthreads


**1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).**

**Particionamento**: 
Uma das primeiras tarefas para desenvolver um programa paralelo é quebrar o problema em pequenos "pedaços" para que possam ser distribuídos pra diversas tarefas. Isso ocorre na seguinte parte do código:

```c
void *dotprod_worker(void *arg)
{
   int i, k;
   long offset = (long) arg;
   double *a = dotdata.a;
   double *b = dotdata.b;     
   int wsize = dotdata.wsize;
   int start = offset*wsize;
   int end = start + wsize;
   double mysum;

   for (k = 0; k < dotdata.repeat; k++) {
      mysum = 0.0;
      for (i = start; i < end ; i++)  {
         mysum += (a[i] * b[i]);
      }
   }

   pthread_mutex_lock (&mutexsum);
   dotdata.c += mysum;
   pthread_mutex_unlock (&mutexsum);

   pthread_exit((void*) 0);
}
```

**Comunicação**:
A necessidade de comunicação entre as tarefas pode ser visualizada nas structs *dotdata_t*, e *pthread_mutex_t*. As variáveis *dotdata* e *mutexsum* são globais e acessíveis por todas as threads.  


**Aglomeração**:
Agrupar tarefas em tarefas maiores para diminuir o tempo de comunicação (entre outras coisas).

Pode ser visto em:
```c
for (k = 0; k < dotdata.repeat; k++) {
   mysum = 0.0;
   for (i = start; i < end ; i++)  {
      mysum += (a[i] * b[i]);
   }
}
pthread_mutex_lock (&mutexsum);
dotdata.c += mysum;
pthread_mutex_unlock (&mutexsum)
```

Onde o laço realiza a multiplicação e adiciona à variável *mysum*. Então o conteúdo da variável é acrescentado à struct que está dentro do mutex.

**Mapeamento**:
Maximizar a ocupação dos processadores e minimizar a comunicação entre processadores, atribuindo tarefas de maneira distribuída.
Na função *dotprod_threads* temos o seguinte trecho, utilizado para a distribuição de tarefas entre threads:
```c
for (i = 0; i < nthreads; i++) {
    pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
}
```

**2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?**

A aceleração foi de ~1.89.

**3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições?**
Sim, a aceleração aumenta com até 4 threads, o que faz sentido, pois o processador tem dois cores e quatro threads. Analisando os gráficos presentes na próxima questão conseguimos ver uma aceleração considerável com 2 threads, e uma melhor ainda com 4 threads.


**4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.**

Cada tabela é o resultado da média de 20 execuções na shell. 

| Tamanho do vetor (500 repetições) | 1 thread | 2 threads | 4 threads | 8 threads | Speedup 2 | Speedup 4 | Speedup 8 |
|-----------------------------------|----------|-----------|-----------|-----------|-----------|-----------|-----------|
| 2000000                           | 3614534  | 2210936   | 1731452   | 1768344   | ~1.6      | ~2        | ~2        |
| 1000000                           | 1804996  | 1058902   | 880400    | 874679    | ~1.7      | ~2        | ~2        |
| 10000                             | 19419    | 13344     | 10417     | 9811      | ~1.4      | ~1.86     | ~1.9      |

| Tamanho do vetor (1000 repetições) | 1 thread | 2 threads | 4 threads | 8 threads | Speedup 2 | Speedup 4 | Speedup 8 |
|------------------------------------|----------|-----------|-----------|-----------|-----------|-----------|-----------|
| 2000000                            | 7185334  | 4382029   | 3840643   | 3759694   | ~1.63     | ~1.87     | ~1.9      |
| 1000000                            | 3599040  | 2171332   | 1761621   | 1817390   | ~1.65     | ~2        | ~1.98     |
| 10000                              | 36373    | 26790     | 15391     | 16033     | ~1.35     | ~2.2      | ~2.2      |



**5. Explique as diferenças entre pthreads_dotprod.c e pthreads_dotprod2.c. Com as linhas removidas, o programa está correto?**
O arquivo *pthreads_dotprod2.c* não utiliza de mutex no momento de inserção da soma na estrutura de dados. Não está correto, pois apesar de algumas vezes o resultado ser igual, em outros casos pode ocasionar em inconsistências no resultado, quando duas ou mais threads tentam acessar a mesma variável.



### OpenMP

**1. Implemente um programa equivalente a pthreads_dotprod.c usando OpenMP.**

O arquivo pode ser conferido em [openmp_pthreads_dotprod.c](openmp/openmp_pthreads_dotprod.c)

**2. Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX.**

| Tamanho do vetor (500 repetições) | Speed Up 2 (Pthread) | Speed Up 2 (OpenMP) | Speed Up 4 (Pthread) | Speed Up 4 (OpenMP) | Speed Up 8 (Pthread) | Speed Up 8 (OpenMP) |
|-----------------------------------|----------------------|---------------------|----------------------|---------------------|----------------------|---------------------|
| 2000000                           | ~1.6                 |  ~2.28              | ~2                   |  ~2.57                   | ~2                   |       ~2.65              |
| 1000000                           | ~1.7                 |    ~2.33                 | ~2                   |  ~2.47                   | ~2                   |   ~2.50                  |
| 10000                             | ~1.4                 |    ~2.39                 | ~1.86                |     ~2.56                | ~1.9                 |     ~2.66                |


| Tamanho do vetor (1000 repetições) | Speed Up 2 (Pthread) | Speed Up 2 (OpenMP) | Speed Up 4 (Pthread) | Speed Up 4 (OpenMP) | Speed Up 8 (Pthread) | Speed Up 8 (OpenMP) |
|------------------------------------|----------------------|---------------------|----------------------|---------------------|----------------------|---------------------|
| 2000000                            | ~1.63                | ~2.76               | ~1.87                |  ~2.81               | ~1.9                 | ~2.83                    |
| 1000000                            | ~1.65                | ~2.21                    | ~2                   |  ~2.44                   | ~1.98                |   ~2.52                  |
| 10000                              | ~1.35                |   ~2.52                  | ~2.2                 |    ~2.66                 | ~2.2                 |  ~2.69                   |


Como visto acima há uma boa diferença no Speed Up comparando com o OpenMP. Podemos ver, analisando o máximo e mínimo do OpenMP - 2.21 e 2.83 - que até o mínimo do OpenMp é superior a maioria dos Speed Up usando Pthread.
