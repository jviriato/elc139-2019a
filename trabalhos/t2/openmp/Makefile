# GNU Makefile

CC = gcc 
CCFLAGS = -Wall
LDFLAGS = -fopenmp
TARGET = ompsimple openmp_pthreads_dotprod

%.o: %.c
	$(CC) $(CCFLAGS) -c $<

%: %.o
	$(CC) $(LDFLAGS) $^ -o $@ 

all: $(TARGET)

# Dependencias

openmp_pthreads_dotprod: openmp_pthreads_dotprod.c
ompsimple: ompsimple.c

clean:
	rm -f *.o *~ $(TARGET)
