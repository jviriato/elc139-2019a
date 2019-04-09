# T3: Scheduling com OpenMP


## Programação Paralela - ELC139-2019a

**Nome:** José Victor Viriato 

**Programa**: [OpenMPDemoABC.cpp](/trabalhos/t3/OpenMPDemoABC.cpp)

**Resultados**: [Results](/trabalhos/t3/output.txt)

## Explicações

**Static:** É decidido no início qual thread será responsável por quais valores.
Chunk = 1: Intercala entre iterações

**Dynamic:** Cada thread irá trabalhar num valor de chunks, e quando terminar irá
trabalhar no próximo chunk não ocupado.

**Guided:** 
"Similar à dinâmica, mas o tamanho de chunk começa grande e decrementa para lidar com
o desbalanceamento entre iterações.[¹]

**Runtime:** Usa a variável OMP_schedule para especificar qual tipo de scheduling usar.

**Auto:** É delegado ao compilador.

  ## Referências

- [Intel](https://software.intel.com/en-us/articles/openmp-loop-scheduling)  
  OpenMP* Loop Scheduling.