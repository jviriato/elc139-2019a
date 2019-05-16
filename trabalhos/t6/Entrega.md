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

**Código**: [matrix_mult_sr_fixed.c](matrix_mult_sr_fixed.c)


## Parte 2

O autor, Sergei Gorlatch, da *Universität Münster*, localizada na Alemanha, em seus capítulos iniciais, comenta sobre o famoso paper de Dijkstra *GOTO considered harmful* publicado em 1968, onde Dijkstra afirmava que o GOTO deixava programas sequenciais muito complexos, sendo possível escrever qualquer programa sem a utilização de GOTO. A partir desse paper, a programação estruturada foi maturada para algo próximo do que temos hoje em dia. Gorlatch compara GOTO com Send/Receive no âmbito da programação paralela, e sugere que tal qual a eliminação de GOTO foi revolucionária na programação estruturada, a substituição de Send/Receive pode ser de importância equivalente para a programação paralela.

Gorlatch sugere que seja usadas as *collective operations* como alternativa ao Send/Receive. Elas já estão estabelecidas no padrão MPI. Ao afirmar isso, ele aplica algumas formas de mensurar a qualidade dos códigos: Simplicidade (o programa é mais simples e compreensível?), Programabilidade (Algum processo sistemático do design do programa foi facilidado?), Expressividade (Classes importantes das aplicações podem ser expressadas com clareza?), Performance (A performance é competitiva com seu contraponto Send/Receive?), e Predictabilidade (O comportamento do programa e sua performance são mais predizíveis?). As sessões do paper são estruturadas cada um com uma afirmação pró Send/Receive (um "Mito", segundo o autor), e então refutada.

Na sessão 3, é abordada a Simplicidade. O mito afirma que as primitivas Send/Receive são maneiras simples de especificar comunicação em programas paralelos. Porém, não existe maneira efetiva para debuggar e entender esse programa, pois não há um conjunto de coordenadas que descrevem o progresso dele.
Além disso, existem oito tipos de *send* e 2 de *receive*. O que deixa as coisas ainda menos compreensíveis.


Na sessão 4, é comentado sobre a Programibilidade. O mito afirma que o design de programas paralelos é tão complicado que nunca será um processo sistemático. Porém, o design pode ser facilitado atráves de *collective operations* de alto-nível.

Na quinta sessão, o mito é sobre Expressividade. Este diz que *collective operations* não são flexíveis o suficiente para expressar aplicações importantes. O autor então, apresenta exemplos de aplicações que se baseiam inteiramente nas *collective operations*.

Performance é o assunto da 6 sessão. É afirmado que programas Send/Receive são mais rápidos. Por *collective operations* serem implementadas com Send/Receive, naturalmente elas serão mais rápidas. Entretanto, isso não é totalmente verdade. É comum as *collective operations* serem implementadas a nível de hardware, e por conta disso, em casos específicos, Send/Receive pode ser até mesmo mais lento.

Em sua sétima sessão, o mito diz que informações confiáveis de performance só podem ser obtidas após o programa ser executado. É verdade que é complicado predizer a performance de um programa Send/Receive. Mas com a utilização de *collective operations*, a sua predicabilidade pode ser simplificada.




## Referências
[1] [MPI_Bcast](https://www.mpich.org/static/docs/v3.2/www3/MPI_Bcast.html)

[2] [MPI_Scatter](https://www.mpich.org/static/docs/v3.1/www3/MPI_Scatter.html)

[3] [MPI Scatter, Gather, and Allgather](https://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/zh_cn/)
