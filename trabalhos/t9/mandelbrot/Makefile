FLAGS=-O3 --expt-relaxed-constexpr

RM=rm -f

EXEC=mandelbrot

all: $(EXEC)

$(EXEC):
	nvcc $(EXEC).cu -o $(EXEC) $(FLAGS)

clean:
	$(RM) $(EXEC).o $(EXEC)

