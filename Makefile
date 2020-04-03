# Macros:
CPP= g++
CFLAGS= -O3 -fopenmp
OBJECTS= SampleDecoder.o main.o bossa_timer.o

# Targets:
all: main

main: $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o main

SampleDecoder.o: SampleDecoder.cpp
	$(CPP) $(CFLAGS) -c SampleDecoder.cpp

bossa_timer.o: bossa_timer.cpp
	$(CPP) $(CFLAGS) -c bossa_timer.cpp

# Remove:
clean:
	rm -f main $(OBJECTS)
