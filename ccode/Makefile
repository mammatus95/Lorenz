CC=gcc
CSTD=-std=c11
CFLAGS=-c -Wall
CWARN=-Wextra -Wpedantic
SPEED=-O
OMP=-fopenmp
#DEBUG=-g

OBJ_lorenz=lorenz.o lorenzlib.o
OBJ_lorenzdiv=lorenzdiv.o lorenzlib.o
ALL=lorenz lorenzdiv

all: $(ALL) 
lorenz: $(OBJ_lorenz)
	$(CC) -o $@ $^ $(CSTD) $(CWARN)
	
lorenzdiv: $(OBJ_lorenzdiv)
	$(CC) -o $@ $^ $(CSTD) $(OMP) 

%.o: %.cpp
	$(CC) -o $@ $< $(CSTD) $(OMP) $(CFLAGS) $(SPEED)

clean:
	rm -rf *.o $(ALL) 
