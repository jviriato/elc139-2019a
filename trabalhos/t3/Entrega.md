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

Os casos Static, Dynamic e Guided foram executados com e sem chunks. 

Todos os casos foram executados com e sem exclusão mútua. Analisando os resultados, percebemos que casos sem exclusão mútua são sucetíveis à erros.  

```
$ cat results.txt
Aplicações com mutex: 

Caso 1: Static schedule sem chunks
BCAAAAAAACBBCCCCCCCBBBBBBBBBBBBBBAAAAAAAAAAAAABBBCCCCCCCCCCC
A=20 B=20 C=20 
Caso 2: Static schedule com chunks
CAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCC
A=20 B=20 C=20 
Caso 3: Dynamic schedule sem chunks
CBBBBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACB
A=53 B=5 C=2 
Caso 4: Dynamic schedule com chunks
BCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCBBBBAAAAA
A=5 B=5 C=50 
Caso 5: Guided schedule sem chunks
BAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCC
A=26 B=20 C=14 
Caso 6: Guided schedule com chunks
CBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAACCCCCCCCCCCCCCCCCCC
A=9 B=31 C=20 
Caso 7: Runtime schedule
CAAAAAAAACCCABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCA
A=10 B=45 C=5 
Caso 8: Auto schedule
AAAAAAAACCCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAP$�6Vx<
A=28 B=0 C=20 

Aplicações sem mutex: 

Caso 1: Static schedule sem chunks
AACBACBACBACBACABACBACBACBACABCCABCABCABCBACBCABCACBACBA-B-B
A=20 B=19 C=19 
Caso 2: Static schedule com chunks
ACABCABCBACBACBACBACBACBACBACBCABCBCABCABCABCABCABCABCAB-A-A
A=20 B=19 C=19 
Caso 3: Dynamic schedule sem chunks
CABCACBABCABCABCACBACBABCABCABCACBBCBACABCABCABCABCABABCAB--
A=19 B=20 C=19 
Caso 4: Dynamic schedule com chunks
ABCACBACBABACBACBACBACBACACABCABCABCABCABCBACBACBACBACBA-CB-
A=20 B=19 C=19 
Caso 5: Guided schedule sem chunks
AACBACBACBACBACABACBACBACBACBABACBACBBACBACBACBACBCBABCABC--
A=20 B=20 C=18 
Caso 6: Guided schedule com chunks
ABCABCABCABCABCABCABCBACBACBACBACBACBABCABCABACBACABCABAC--C
A=20 B=19 C=19 
Caso 7: Runtime schedule
ABACABCABCABCACBACBACBACABCABACBABACBABCABCABCBACBACBACBAC--
A=21 B=19 C=18 
Caso 8: Auto schedule
BACBACBACBABACBACBBACBACBACBACBCBABCABC--!
A=12 B=15 C=12 
```


  ## Referências

- [Intel](https://software.intel.com/en-us/articles/openmp-loop-scheduling)  
  OpenMP* Loop Scheduling.
